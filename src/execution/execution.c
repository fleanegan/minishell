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
			exit(built_in_array[i].func_ptr(env, content));
		i++;
	}
	return (0);
}

void	execute_execve(t_cmd *content, t_list *env)
{
	if (execute_as_built_in(content, env) == 0 \
		&& access(content->exec_name, X_OK) == 0)
	{
		fprintf(stderr, "this is NOT builtin\n");
		execve(content->exec_name, content->args, NULL);
	}
	perror(content->exec_name);
	(void) env;
}

void	exec_child(t_list *cmd, int i, int **fd, t_list *env)
{
	t_cmd	*content;

	content = get_content(cmd);
	if ((content->outtoken == REDIR_OUT_REPLACE \
		|| content->outtoken == REDIR_OUT_APPEND) \
		&& redirect_stdout_to_outfile(content->outfile, content->outtoken))
		exit(close_before_exit_process(fd));
	else if (content->outtoken == PIPE \
		&& redirect_stdout_into_pipe(fd[i]))
		exit(close_before_exit_process(fd));
	if (content->intoken == EMPTY && cmd->prev != NULL \
		&& redirect_stdin_into_pipe(fd[i - 1]))
		exit(close_before_exit_process(fd));
	if (content->intoken != EMPTY \
		&& redirect_infile_to_stdin(content->infile))
		exit(close_before_exit_process(fd));
	if (close_before_exit_process(fd) == 1)
		exit(errno);
	execute_execve(content, env);
	exit(errno);
}

int	execution(t_list *cmd, t_list *env, int nb_cmd)
{
	pid_t	pid;
	int		i;
	int		**fd;

	fd = ft_tabnew_two(nb_cmd, 2);
	init_pipes(nb_cmd, fd);
	i = 0;
	while (i < nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			exec_child(cmd, i, fd, env);
		cmd = cmd->next;
		i++;
	}
	if (pid != 0)
		return (tear_down_parent(nb_cmd, fd, pid));
	return (0);
}

int	tear_down_parent(int nb_processes, int **fd, int pid_of_last_cmd)
{
	int	wait_result_buffer;
	int	last_result;
	int	i;
	int	pid_return;

	i = 0;
	last_result = 0;
	if (close_before_exit_process(fd) == 1 && ! free_2d_array((void **) fd))
		return (-1);
	while (i < nb_processes)
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
	free_2d_array((void **) fd);
	return (last_result);
}
