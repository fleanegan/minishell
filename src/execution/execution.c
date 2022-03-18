#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"

void	execution(t_list *cmd, char *env)
{
	pid_t	pid;

	(void)	env;
	if (cmd == NULL)
		return ;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		execve(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
		perror("minishell");
		exit(0);
	}
	if (pid != 0)
	{
		while (42)
		{
			if (waitpid(pid, NULL, WNOHANG) == pid)
			{
				kill(pid, SIGTERM);
				return ;
			}
		}
	}
}
