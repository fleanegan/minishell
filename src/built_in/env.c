#include "../minishell.h"

int msh_env(t_list *env, t_cmd *cmd)
{
	puts("printing msh_env");
	while (env)
	{
		ft_putstr_fd(((t_dict_entry *)env->content)->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(((t_dict_entry *)env->content)->value, 1);
		env = env->next;
	}
	return (0);
	(void) cmd;
}