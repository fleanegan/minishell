#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"

void exec_child(t_list *cmd, int i, int nb_cmd, int **fd);

int tear_down_parent(int i, int nb_cmd, int **fd);

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
		if (pid == 0)
			exec_child(cmd, i, nb_cmd, fd);
		cmd = cmd->next;
		i++;
	}
	if (pid != 0)
		tear_down_parent(i, nb_cmd, fd);
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

int	tear_down_parent(int i, int nb_cmd, int **fd)
{
	int	last_status;

	if (close_before_exit_process(fd, nb_cmd) == 1)
		exit (1);
	while (i > 0)
	{
		if (wait(&last_status) == -1)
			perror("wait");
		i--;
	}
	free_2d_array((void **) fd);
	if ( WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (0);
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
	if (i == 0)
	{
		execve(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
		perror(get_content(cmd)->exec_name);
		exit(errno);
	}
	if (i != 0)
	{
		redirect_stdin_into_pipe(fd[i - 1]);
		if (close_before_exit_process(fd, nb_cmd) == 1)
			exit (1);
		execve(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
		perror(get_content(cmd)->exec_name);

	}
	if (close_before_exit_process(fd, nb_cmd) == 1)
		exit(1);
	exit(errno);
}
