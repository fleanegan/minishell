#include "minishell.h"

int	append_to_dict(t_list **dict, char *key, char *value)
{
	t_dict_entry	*tmp_entry;
	t_list	*tmp_node;

	tmp_entry = malloc(sizeof(t_dict_entry));
	if (tmp_entry == NULL)
		return (1);
	tmp_entry->key = ft_strdup(key);
	tmp_entry->value = ft_strdup(value);
	tmp_node = ft_lstnew(tmp_entry);
	if (tmp_node == NULL)
		return (1);
	ft_lstadd_back(dict, tmp_node);
	return (0);
}

t_list	*init()
{
	t_list	*result;

	if (set_signal_handler(SIGINT, handle_ctrl_c) \
		|| set_signal_handler(SIGQUIT, handle_ctrl_backslash))
	{
		puts("error in init");
		return (NULL);
	}
	result = NULL;

	if (append_to_dict(&result, "HOME", getenv("HOME")) \
		|| append_to_dict(&result, "PATH", getenv("PATH"))
		|| append_to_dict(&result, "X", "TEST")
		|| append_to_dict(&result, "?", "0")
		|| append_to_dict(&result, "PWD", getenv("PWD")))
	{
		puts("error initiating env");
		ft_lstclear(&result, free_dict_entry);
		return (NULL);
	}
	return (result);
}
