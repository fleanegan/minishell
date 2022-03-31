#include "../inc/minishell.h"

int	init_env(t_list **env, char **envp)
{
	if (envp == NULL)
		return (0);
	while (*envp)
	{
		if (append_str_to_env(env, *envp))
		{
			ft_putendl_fd("error while parsing envp", 2);
			ft_lstclear(env, free_dict_entry);
			return (1);
		}
		envp++;
	}
	return (0);
}

t_list	*init(char **envp)
{
	t_list	*result;

	result = NULL;
	if (set_signal_handler(SIGINT, handle_ctrl_c) \
		|| set_signal_handler(SIGQUIT, NULL))
	{
		puts("error in init");
		return (NULL);
	}
	if (update_env(&result, "?", "0", ENV_REPLACE_VAR) \
		|| init_env(&result, envp) == 1)
	{
		puts("error initiating msh_env");
		ft_lstclear(&result, free_dict_entry);
		return (NULL);
	}
	return (result);
}
