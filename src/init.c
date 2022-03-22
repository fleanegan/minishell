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

	if (update_env(&result, "HOME", getenv("HOME")) \
		|| update_env(&result, "PATH", getenv("PATH"))
		|| update_env(&result, "X", "TEST")
		|| update_env(&result, "?", "0")
		|| update_env(&result, "PWD", getenv("PWD")))
	{
		puts("error initiating env");
		ft_lstclear(&result, free_dict_entry);
		return (NULL);
	}
	return (result);
}
