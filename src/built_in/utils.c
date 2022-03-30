#include "../minishell.h"

static int	cmp_dict_entry_on_key(void *first, void *second)
{
	return ((ft_strcmp(((t_dict_entry *)(first))->key, \
	((t_dict_entry *)(second))->key)) <= 0);
}

int	append_str_to_env(t_list **env, char *input)
{
	char	*key;
	char	*value;
	int		result;
	char	*pos_of_eq;

	result = 0;
	pos_of_eq = ft_strchr(input, '=');
	if (pos_of_eq == NULL)
		return (0);
	key = append_str(ft_strdup(""), input, calc_key_len(input));
	value = append_str(ft_strdup(""), pos_of_eq + 1, ft_strlen(pos_of_eq - 1));
	if (key == NULL || value == NULL)
		result = ENOMEM;
	if (result == 0 && *(pos_of_eq - 1) == '+')
		result = update_env(env, key, value, ENV_APPEND_VAR);
	if (result == 0 && *(pos_of_eq - 1) != '+')
		result = update_env(env, key, value, ENV_REPLACE_VAR);
	free(key);
	free(value);
	return (result);
}

int	append_to_env(t_list **env, char *key, char *value)
{
	t_dict_entry	*tmp_entry;
	t_list			*tmp_node;

	tmp_entry = malloc(sizeof(t_dict_entry));
	if (tmp_entry == NULL)
		return (ENOMEM);
	tmp_entry->key = ft_strdup(key);
	tmp_entry->value = ft_strdup(value);
	tmp_node = ft_lstnew(tmp_entry);
	if (tmp_entry->key == NULL || tmp_entry->value == NULL || tmp_node == NULL)
	{
		free(tmp_entry->key);
		free(tmp_entry->value);
		free(tmp_entry);
		ft_lstclear(&tmp_node, free_dict_entry);
		return (ENOMEM);
	}
	ft_lstadd_back(env, tmp_node);
	return (0);
}

int	update_env(t_list **env, char *key, char *val, t_env_mode update_mode)
{
	t_dict_entry	*current;

	if (env == NULL || key == NULL)
		return (1);
	current = get_entry_by_key(*env, key);
	if (current != NULL)
	{
		if (update_mode == ENV_APPEND_VAR)
		{
			current->value = append_str(current->value, val, ft_strlen(val));
			if (current->value == NULL)
				return (ENOMEM);
		}
		else
		{
			free(current->value);
			current->value = ft_strdup(val);
			if (current->value == NULL)
				return (ENOMEM);
		}
	}
	else if (append_to_env(env, key, val))
		return (ENOMEM);
	ft_lstsort(env, cmp_dict_entry_on_key);
	return (0);
}
