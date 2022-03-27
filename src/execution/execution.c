#include "minishell.h"

void * get_built_in_function_pointer(const t_cmd *content)
{
	int							i;
	size_t						max;
	const t_built_in_entry		built_in_array[NB_BUILT_INS] = {
	{"env", msh_env},
	{"cd", msh_cd},
	{"export", msh_export},
	{"echo", msh_echo},
	{"pwd", msh_pwd},
	{"unset", msh_unset}};

	i = 0;
	while (i < NB_BUILT_INS)
	{
		max = calc_max_unsigned(\
		ft_strlen(content->args[0]), \
		ft_strlen(built_in_array[i].name));
		if (ft_strncmp(content->args[0], built_in_array[i].name, max) == 0)
			return (built_in_array[i].func_ptr);
		i++;
	}
	return (NULL);
}

int execute_execve(t_cmd *content, t_list *env)
{
	char	**env_char;
	void	*target;

	target = get_built_in_function_pointer(content);
	if (target == NULL)
	{
		if (access(content->exec_name, X_OK) != 0)
			return (errno);
		env_char = (char **) to_array(env, cpy_dict_to_str);
		set_sa_handler(SIGINT, NULL);
		execve(content->exec_name, content->args, env_char);
		//TODO : free env_char if execve error
		return (errno);
	}
	return (((int(*)(t_list **, t_cmd *))target)(&env, content));
	(void) env_char;
}

int exec_child(t_list *cmd, int i, int **fd, t_list *env)
{
	t_cmd	*content;

	content = get_content(cmd);
	if ((content->outtoken == REDIR_OUT_REPLACE \
		|| content->outtoken == REDIR_OUT_APPEND) \
		&& redirect_stdout_to_outfile(content->outfile, content->outtoken))
		return(close_before_exit_process(fd));
	if (content->pipe == PIPE && content->outtoken == EMPTY \
		&& redirect_stdout_into_pipe(fd[i]))
		return(close_before_exit_process(fd));
	if (content->intoken == EMPTY && cmd->prev != NULL \
		&& redirect_stdin_into_pipe(fd[i - 1]))
		return(close_before_exit_process(fd));
	if (content->intoken != EMPTY \
		&& redirect_infile_to_stdin(content->infile))
		return(close_before_exit_process(fd));
	if (close_before_exit_process(fd) == 1)
		return(errno);
	return(execute_execve(content, env));
}

int	execution(t_list *cmd, t_list *env, int nb_cmd)
{
	pid_t	pid;
	int		i;
	int		**fd;
	int		built_in_count;
	int		ret_builtin;

	ret_builtin = 0;
	built_in_count = 0;
	set_sa_handler(SIGINT, SIG_IGN);
	fd = ft_tabnew_two(nb_cmd, 2);
	init_pipes(nb_cmd, fd);
	i = 0;
	while (i < nb_cmd)
	{
		if (get_built_in_function_pointer(cmd->content) != NULL && nb_cmd == 1)
		{
			ret_builtin = exec_child(cmd, i, fd, env); // check result
			if (ret_builtin != 0)
				perror(get_content(cmd)->args[0]);
			built_in_count++;
		}
		else
		{
			pid = fork();
			if (pid == -1)
				return (-1);
			if (pid == 0)
			{
				if (exec_child(cmd, i, fd, env))
					perror(get_content(cmd)->args[0]);
				exit(errno);
			}
		}
		cmd = cmd->next;
		i++;
	}
	if (pid != 0)
		return (tear_down_parent(nb_cmd, fd, pid, built_in_count));
	return (ret_builtin);
}

int tear_down_parent(int nb_processes, int **fd, int pid_of_last_cmd, int built_in_count)
{
	int	wait_result_buffer;
	int	last_result;
	int	i;
	int	pid_return;

	i = 0;
	last_result = 0;
	if (close_before_exit_process(fd) == 1 && ! free_2d_array((void **) fd))
		return (-1);
	while (i < nb_processes - built_in_count)
	{
		pid_return = wait(&wait_result_buffer);
		if (pid_return == -1)
			perror("wait");
		if (pid_return == pid_of_last_cmd)
		{
			if (WIFEXITED(wait_result_buffer))
				last_result = WEXITSTATUS(wait_result_buffer);
		}
		i++;
	}
	if (set_signal_handler(SIGINT, handle_ctrl_c))
		return (errno);
	free_2d_array((void **) fd);
	return (last_result);
}
