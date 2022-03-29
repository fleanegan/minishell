#include "../minishell.h"

int	exec_cmd(t_list *cmd, int i, int **fd, t_list *env)
{
	t_cmd	*content;

	content = get_content(cmd);
	if ((content->outtoken == REDIR_OUT_REPLACE \
		|| content->outtoken == REDIR_OUT_APPEND) \
		&& redirect_stdout_to_outfile(content->outfile, content->outtoken))
		return (close_before_exit_process(fd));
	if (content->pipe == PIPE && content->outtoken == EMPTY \
		&& redirect_stdout_into_pipe(fd[i]))
		return (close_before_exit_process(fd));
	if (content->intoken == EMPTY && cmd->prev != NULL \
		&& redirect_stdin_into_pipe(fd[i - 1]))
		return (close_before_exit_process(fd));
	if (content->intoken != EMPTY \
		&& redirect_infile_to_stdin(content->infile))
		return (close_before_exit_process(fd));
	if (close_before_exit_process(fd) == 1)
		return (errno);
	return (execute_execve(content, env));
}

pid_t	execute_cmd_in_fork(t_list *cmd, t_list *env, int i, int **fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_2d_array((void **) fd);
		return (-1);
	}
	if (pid == 0)
	{
		if (exec_cmd(cmd, i, fd, env))
			perror(get_content(cmd)->args[0]);
		exit(errno);
	}
	return (pid);
}
