#include "minishell.h"

t_cmd	*get_content(t_list *in)
{
	if (in == NULL)
		return (NULL);
	return (((t_cmd *)((in)->content)));
}

int	calc_key_len(char *key)
{
	int	i;

	i = 0;
	if (key == NULL || ft_isdigit(key[i]))
		return (0);
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	return (i);
}

t_dict_entry	*get_value_by_key(t_list *lst, char *key)
{
	while (lst)
	{
		if (ft_strncmp(((t_dict_entry *) (lst->content))->key, key, calc_key_len(key)) == 0)
			return ((t_dict_entry *) (lst->content));
		lst = lst->next;
	}
	return (NULL);
}