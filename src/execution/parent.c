#include "../minishell.h"

int	execute_built_in_parent(t_list *cmd, t_list *env, int i, int **fd)
{
	int	saved_stdout;
	int	ret_builtin;

	ret_builtin = 0;
	get_content(cmd)->intoken = EMPTY;
	free(get_content(cmd)->infile);
	get_content(cmd)->infile = NULL;
	saved_stdout = dup(1);
	if (saved_stdout < 0)
		return (errno);
	ret_builtin = exec_cmd(cmd, i, fd, env);
	if (dup2(saved_stdout, 1) && ft_close(&saved_stdout))
		return (errno);
	free_2d_array((void **) fd);
	return (ret_builtin);
}

int	tear_down_parent(int nb_processes, int **fd, int pid_of_last_cmd)
{
	int	wait_result_buffer;
	int	last_result;
	int	i;
	int	pid_return;

	i = 0;
	last_result = 0;
	if (close_before_exit_process(fd) == 1 && free_2d_array((void **) fd) == 0)
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
	if (set_signal_handler(SIGINT, handle_ctrl_c))
		return (errno);
	return (last_result);
}
