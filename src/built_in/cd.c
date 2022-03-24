#include "../minishell.h"

int	msh_cd(t_list *env, t_cmd *cmd)
{
	(void) env;
	if (cmd->args[1] == NULL)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		return (2);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		perror("cd");
		return (errno);
	}
	char s[2048];
	printf("inside cd. updating path to : %s\n", getcwd(s, 2048));
	update_env(&env, "PWD", getcwd(s, 2048));
	return (0);
}