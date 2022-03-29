#include "../minishell.h"

int msh_env(t_list **env, t_list **cmd, int index)
{
	return (print_all_env_vars_with_prefix(env, ""));
	(void) cmd;
	(void) index;
}

int print_all_env_vars_with_prefix(t_list **env, char *prefix)
{
	while (*env)
	{
		if (((t_dict_entry *)(*env)->content)->key[0] != '?')
		{
			ft_putstr_fd(prefix, 1);
			ft_putstr_fd(((t_dict_entry *)(*env)->content)->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(((t_dict_entry *)(*env)->content)->value, 1);
		}
		*env = (*env)->next;
	}
	return (0);
}
