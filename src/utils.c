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
	if (key == NULL || key[i] == 0 || ft_isdigit(key[i]))
		return (0);
	key++;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	return (i);
}

t_dict_entry	*get_value_by_key(t_list *lst, char *key)
{
	char	*key_without_dollar;

	key_without_dollar = key + 1;
	while (lst)
	{
		if (ft_strncmp(((t_dict_entry *) (lst->content))->key, key_without_dollar , calc_key_len(key)) == 0)
			return ((t_dict_entry *) (lst->content));
		lst = lst->next;
	}
	return (NULL);
}