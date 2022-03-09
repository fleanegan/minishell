#include "minishell.h"

void	execution(char *path, char **args, char *env)
{
	(void)	args;
	(void)	env;
	char	*argv[] = { "test", NULL };
	execve(path, argv, NULL);
	perror("minishell");
}
