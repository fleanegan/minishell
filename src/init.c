#include "minishell.h"

int	append_new_entry_to_dict(t_list **dict, char *key, char *value)
{
	t_dict	*tmp_entry;
	t_list	*tmp_node;

	tmp_entry = malloc(sizeof(t_dict));
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
		return (NULL);
	result = NULL;

	if (append_new_entry_to_dict(&result, "HOME",getenv("HOME")))
	{
		//ft_lstclear(&result, );
		return (NULL);
	}
	return (result);
}

char	*get_value_by_key(t_list *lst, char *key)
{
	size_t	max_len;

	while (lst)
	{
		max_len = calc_max_unsigned(\
                            ft_strlen(((t_dict *) (lst->content))->value), \
                            ft_strlen(key));
		if (ft_strncmp(((t_dict *) (lst->content))->key, key, max_len) == 0)
			return (((t_dict *) (lst->content))->value);
		lst = lst->next;
	}
	return (NULL);
}