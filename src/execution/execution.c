#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"

int	execution(t_list *cmd, char *env)
{
	pid_t	pid;
	int		i;
	int		nb_cmd = ft_lstsize(cmd);
	int		**fd = ft_tabnew_two(nb_cmd, 2);

	(void) env;
	i = 0;
	while (i < nb_cmd)
	{
		pipe(fd[i]);
		i++;
	}
	i = 0;
	while (i < nb_cmd)
	{
		pid = fork();
		if (pid == 0) // child
		{
			if (i != nb_cmd - 1)
			{
				ft_close(&fd[i][0]);
				dup2(fd[i][1], 1);
				ft_close(&fd[i][1]);
			}
			if (i == 0)
			{
				execve(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
				perror("execve ls");
			}
			if (i != 0)
			{
				ft_close(&fd[i - 1][1]);
				dup2(fd[i - 1][0], 0);
				ft_close(&fd[i - 1][0]);

				if (close_before_exit_process(fd, nb_cmd) == 1)
					exit (1);
				execve(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
				perror("execve cat");
			}
			if (close_before_exit_process(fd, nb_cmd) == 1)
				exit (1);
			exit(0);
		}
		if (pid != 0) // parent
			cmd = cmd->next;
		i++;
	}
	if (pid != 0) // parent
	{
		if (close_before_exit_process(fd, nb_cmd) == 1)
			exit (1);
		while (i > 0)
		{
			if (wait(NULL) == -1)
				perror("wait");
			i--;
		}
		ft_destroy_tab_two(fd, nb_cmd);
	}
	return (0);
}
