#include "../minishell.h"

int	msh_env(t_list **env, t_list **cmd, int index)
{
	return (print_all_env_vars_with_prefix(env, "", PRINT_ENV));
	(void) cmd;
	(void) index;
}

int	print_all_env_vars_with_prefix(\
	t_list **env, char *prefix, t_print_env_mode mode)
{
	while (*env)
	{
		if (((t_dict_entry *)(*env)->content)->key[0] != '?')
		{
			ft_putstr_fd(prefix, 1);
			ft_putstr_fd(((t_dict_entry *)(*env)->content)->key, 1);
			ft_putstr_fd("=", 1);
			if (mode == PRINT_EXPORT)
				ft_putstr_fd("\"", 1);
			ft_putstr_fd(((t_dict_entry *)(*env)->content)->value, 1);
			if (mode == PRINT_EXPORT)
				ft_putstr_fd("\"", 1);
			ft_putstr_fd("\n", 1);
		}
		*env = (*env)->next;
	}
	return (0);
}

int	calc_key_len(char *key)
{
	int	i;

	i = 0;
	if (key == NULL || key[0] == 0 || key[0] == '_' \
		|| (ft_isalpha(key[0]) == 0 && key[0] != '?'))
		return (0);
	if (key[0] == '?')
		return (1);
	while (key[i] != 0 \
			&& (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	return (i);
}

t_dict_entry	*get_entry_by_key(t_list *lst, char *key_without_dollar)
{
	size_t	max;

	while (lst != NULL && lst->content != NULL)
	{
		max = calc_max_unsigned(\
		ft_strlen(((t_dict_entry *)(lst->content))->key), \
		calc_key_len(key_without_dollar));
		if (ft_strncmp(((t_dict_entry *)(lst->content))->key, \
			key_without_dollar, max) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
