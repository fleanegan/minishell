#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"

void exec_child(t_list *cmd, int i, int nb_cmd, int **fd);
int tear_down_parent(int nb_cmd, int **fd, int pid_of_last_cmd);
void init_pipes(int nb_cmd, int **fd);

int	execution(t_list *cmd, char *env)
{
	pid_t	pid;
	int		i;
	int		nb_cmd;
	int		**fd;

	nb_cmd = ft_lstsize(cmd);
	fd = ft_tabnew_two(nb_cmd, 2);
	init_pipes(nb_cmd, fd);
	i = 0;
	while (i < nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			exec_child(cmd, i, nb_cmd, fd);
		cmd = cmd->next;
		i++;
	}
	if (pid != 0)
		return(tear_down_parent(nb_cmd, fd, pid));
	return (0);
	(void) env;
}

void	init_pipes(int nb_cmd, int **fd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		pipe(fd[i]);
		i++;
	}
}

int tear_down_parent(int nb_cmd, int **fd, int pid_of_last_cmd)
{
	int	wait_result_buffer;
	int	last_result;
	int	i;
	int	pid_return;

	i = 0;
	last_result = 0;
	if (close_before_exit_process(fd, nb_cmd) == 1)
	{
		free_2d_array((void **) fd);
		return (-1);
	}
	while (i < nb_cmd)
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

int	redirect_stdout_into_pipe(int *fd_of_pipe)
{
	if (ft_close(&fd_of_pipe[0]))
		return (1);
	if (dup2(fd_of_pipe[1], STDOUT_FILENO) == -1)
		return (1);
	if (ft_close(&fd_of_pipe[1]))
		return (1);
	return (0);
}

int	redirect_stdin_into_pipe(int *fd_of_pipe)
{
	if (ft_close(&fd_of_pipe[1]))
		return (1);
	if (dup2(fd_of_pipe[0], STDIN_FILENO) == -1)
		return (1);
	if (ft_close(&fd_of_pipe[0]))
		return (1);
	return (0);
}

void exec_child(t_list *cmd, int i, int nb_cmd, int **fd)
{
	if (i != nb_cmd - 1 && redirect_stdout_into_pipe(fd[i]))
	{
		close_before_exit_process(fd, nb_cmd);
		exit(1);
	}
	if (i != 0)
		redirect_stdin_into_pipe(fd[i - 1]);
	if (close_before_exit_process(fd, nb_cmd) == 1)
		exit(1);
	execve(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
	fprintf(stderr, "errno: %d\n", errno);
	perror(get_content(cmd)->exec_name);
	exit(errno);
}
