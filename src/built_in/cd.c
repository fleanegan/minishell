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
	return (0);
}
