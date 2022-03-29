#include "../minishell.h"

int	msh_cd(t_list **env, t_list **cmd, int index)
{
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	if (current_cmd->args[1] == NULL)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		return (2);
	}
	if (chdir(current_cmd->args[1]) == -1)
		return (errno);
	char s[2048];
	//printf("inside cd. updating path to : %s\n", getcwd(s, 2048));
	if (update_env(env, "PWD", getcwd(s, 2048), ENV_REPLACE_VAR))
		return (1);
	return (0);
	(void) env;
}
