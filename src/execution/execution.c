#include "minishell.h"

int	execute_as_built_in(t_cmd *content, t_list *env)
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
			return(built_in_array[i].func_ptr(env, content));
		i++;
	}
	return (-1);
}

int execute_execve(t_cmd *content, t_list *env)
{
	char	**env_char;
	int		result_of_built_in;
	// check result of builtin

	result_of_built_in = execute_as_built_in(content, env);
	if (result_of_built_in == -1 && access(content->exec_name, X_OK) == 0)
	{
		env_char = (char **) to_array(env, cpy_dict_to_str);
		set_sa_handler(SIGINT, NULL);
		if (content->args)
			//printf("ename: %s, arg0: %s, arg1: %s, arg2: %s\n", content->exec_name, content->args[0], content->args[1], content->args[2]);
			fprintf(stderr,"ename: %s, arg0: %s, arg1: %s\n", content->exec_name, content->args[0], content->args[1]);
		else
			puts("no builtirrrrn");
		fprintf(stderr, "ename: %s \n", content->exec_name);
		//puts("wut");
		fflush(stdout);
		execve(content->exec_name, content->args, NULL);
		perror(content->exec_name);
		puts("cantal");
		return (errno);
		(void) env_char;
	}
	return (result_of_built_in);
}

int exec_child(t_list *cmd, int i, int **fd, t_list *env)
{
	t_cmd	*content;

	content = get_content(cmd);
	if ((content->outtoken == REDIR_OUT_REPLACE \
		|| content->outtoken == REDIR_OUT_APPEND) \
		&& redirect_stdout_to_outfile(content->outfile, content->outtoken))
		return(close_before_exit_process(fd));
	else if (content->outtoken == PIPE \
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

	built_in_count = 0;
	set_sa_handler(SIGINT, SIG_IGN);
	fd = ft_tabnew_two(nb_cmd, 2);
	init_pipes(nb_cmd, fd);
	i = 0;
	while (i < nb_cmd)
	{
		fprintf(stderr,"ename: %s\n", get_content(cmd)->exec_name);
		if (msh_strcmp(get_content(cmd)->args[0], "cd") == 0)
		{
			exec_child(cmd, i, fd, env); // check result
			built_in_count++;
		}
		else
		{
			pid = fork();
			if (pid == -1)
				return (-1);
			if (pid == 0)
				exit(exec_child(cmd, i, fd, env));
		}
		cmd = cmd->next;
		i++;
	}
	if (pid != 0)
		return (tear_down_parent(nb_cmd, fd, pid, built_in_count));
	return (0);
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
