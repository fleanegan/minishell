#include "minishell.h"

t_list	*init()
{
	t_list	*result;

	if (set_signal_handler(SIGINT, handle_ctrl_c) \
		|| set_signal_handler(SIGQUIT, NULL))
	{
		puts("error in init");
		return (NULL);
	}
	result = NULL;

	if (update_env(&result, "HOME", getenv("HOME"), ENV_REPLACE_VAR) \
 || update_env(&result, "PATH", getenv("PATH"), ENV_REPLACE_VAR)
		|| update_env(&result, "X", "TEST", ENV_REPLACE_VAR)
		|| update_env(&result, "?", "0", ENV_REPLACE_VAR)
		|| update_env(&result, "PWD", getenv("PWD"), ENV_REPLACE_VAR))
	{
		puts("error initiating msh_env");
		ft_lstclear(&result, free_dict_entry);
		return (NULL);
	}
	return (result);
}
