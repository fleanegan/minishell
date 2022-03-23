#include "minishell.h"

void	execute_execve(t_cmd *content)
{
	if (access(content->exec_name, X_OK) == 0)
		execve(content->exec_name, content->args, NULL);
	perror(content->exec_name);
}


void exec_child(t_list *cmd, int i, int nb_processes, int **fd)
{
	t_cmd *content = get_content(cmd);

	if (i == nb_processes - 1)
	{
		if (i == 0 && content->outtoken != EMPTY \
 			&& redirect_stdout_to_outfile(content->outfile, content->outtoken))
			exit(errno);
	}
	else if (redirect_stdout_into_pipe(fd[i]))
	{
		close_before_exit_process(fd, nb_processes);
		exit(1);
	}
	if (i != 0)
		redirect_stdin_into_pipe(fd[i - 1]);
	if ((i == 0 \
		&& content->intoken != EMPTY \
		&& redirect_infile_to_stdin(content->infile))\
		|| close_before_exit_process(fd, nb_processes) == 1)
		exit(errno);
	execute_execve(content);
	exit(errno);
}


void exec_first_child(t_list *cmd, int i, int nb_processes, int **fd)
{
	t_cmd *content = get_content(cmd);

	if (redirect_stdout_into_pipe(fd[i]))
	{
		close_before_exit_process(fd, nb_processes);
		exit(1);
	}
	if ((i == 0 \
		&& content->intoken != EMPTY \
		&& redirect_infile_to_stdin(content->infile))\
		|| close_before_exit_process(fd, nb_processes) == 1)
		exit(errno);
	execute_execve(content);
	exit(errno);
}

void exec_middle_child(t_list *cmd, int i, int nb_processes, int **fd)
{
	t_cmd *content = get_content(cmd);

	if (redirect_stdout_into_pipe(fd[i]))
	{
		close_before_exit_process(fd, nb_processes);
		exit(1);
	}
	redirect_stdin_into_pipe(fd[i - 1]);
	if (close_before_exit_process(fd, nb_processes) == 1)
		exit(errno);
	execute_execve(content);
	exit(errno);
}

void exec_last_child(t_list *cmd, int i, int nb_processes, int **fd)
{
	t_cmd *content = get_content(cmd);

	if (i == nb_processes - 1)
	{
		if (i == 0 && content->outtoken != EMPTY \
 			&& redirect_stdout_to_outfile(content->outfile, content->outtoken))
			exit(errno);
	}
	else if (redirect_stdout_into_pipe(fd[i]))
	{
		close_before_exit_process(fd, nb_processes);
		exit(1);
	}
	if (i != 0)
		redirect_stdin_into_pipe(fd[i - 1]);
	if (close_before_exit_process(fd, nb_processes) == 1)
		exit(errno);
	execute_execve(content);
	exit(errno);
}

int execution(t_list *cmd, char *env, int nb_cmd)
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
		{
			exec_child(cmd, i, nb_cmd, fd);

//			if (i == 0)
//				exec_first_child(cmd, i, nb_cmd, fd);
//			if (i == nb_cmd - 1 && i != 0)
//				exec_middle_child(cmd, i, nb_cmd, fd);
//			if (i != nb_cmd - 1 && i != 0)
//				exec_last_child(cmd, i, nb_cmd, fd);
		}
		cmd = cmd->next;
		i++;
	}
	if (pid != 0)
		return(tear_down_parent(nb_cmd, fd, pid));
	return (0);
	(void) env;
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


