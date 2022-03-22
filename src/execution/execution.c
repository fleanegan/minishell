#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"

void	exec_child(t_list *cmd, int i, int nb_processes, int **fd);
int		tear_down_parent(int nb_processes, int **fd, int pid_of_last_cmd);
void	init_pipes(int nb_processes, int **fd);
int		redirect_infile_to_stdin(char *infile);

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
	{

		return(tear_down_parent(nb_cmd, fd, pid));
	}
	return (0);
	(void) env;
}

void	init_pipes(int nb_processes, int **fd)
{
	int	i;

	i = 0;
	while (i < nb_processes)
	{
		pipe(fd[i]);
		i++;
	}
}

int tear_down_parent(int nb_processes, int **fd, int pid_of_last_cmd)
{
	int	wait_result_buffer;
	int	last_result;
	int	i;
	int	pid_return;

	i = 0;
	last_result = 0;
	if (close_before_exit_process(fd, nb_processes) == 1)
	{
		free_2d_array((void **) fd);
		return (-1);
	}
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

void exec_child(t_list *cmd, int i, int nb_processes, int **fd)
{
	if (i != nb_processes - 1 && redirect_stdout_into_pipe(fd[i]))
	{
		close_before_exit_process(fd, nb_processes);
		exit(1);
	}
	if (i != 0)
		redirect_stdin_into_pipe(fd[i - 1]);
	if (i == 0 && get_content(cmd)->intoken != EMPTY && redirect_infile_to_stdin(get_content(cmd)->infile))
	{
		exit(errno);
	}
	if (close_before_exit_process(fd, nb_processes) == 1)
		exit(1);
	if (access(get_content(cmd)->exec_name, X_OK) != 0)
		strerror(2);
	else
		execve(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
	perror(get_content(cmd)->exec_name);
	exit(errno);
}

int redirect_infile_to_stdin(char *infile)
{
	int	fd;

	if (access(infile, R_OK) == 0)
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
		{
			perror(infile);
			return (errno);
		}
		else if (dup2(fd, 0))
		{
			ft_putendl_fd("Error", 2);
			return (errno);
		}
	}
	else
	{
		ft_putendl_fd("file is not available for read", 2);
		return (errno);
	}
	return (0);
}
