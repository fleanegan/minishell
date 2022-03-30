#include "minishell.h"

static int	split_input_string_and_store_in_env(\
	t_list **env, char *pos_of_eq, char *input);

int			append_str_to_env(t_list **env, char *input);

static int	cmp_dict_entry_on_key(void *first, void *second)
{
	return ((msh_strcmp(((t_dict_entry *)(first))->key, \
	((t_dict_entry *)(second))->key)) <= 0);
}

int	msh_export(t_list **env, t_list **cmd, int index)
{
	char	*input;
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	if (current_cmd == NULL || current_cmd->args[0] == NULL)
		return (1);
	if (current_cmd->args[1] == NULL)
		return (print_all_env_vars_with_prefix(env, "declare -x ",
				PRINT_EXPORT));
	input = current_cmd->args[1];
	return (append_str_to_env(env, input));
}

int	append_str_to_env(t_list **env, char *input)
{
	char	*pos_of_eq;

	pos_of_eq = ft_strchr(input, '=');
	if (pos_of_eq == NULL)
		return (0);
	if (pos_of_eq == input \
		|| calc_key_len(input) + (pos_of_eq[-1] == '+') != pos_of_eq - input)
	{
		// TODO: distinguish between input error and malloc failure
		return (0);
	}
	return (split_input_string_and_store_in_env(env, pos_of_eq, input));
}

int	split_input_string_and_store_in_env(\
	t_list **env, char *pos_of_eq, char *input)
{
	char	*key;
	char	*value;
	int		result;

	result = 0;
	key = append_str(ft_strdup(""), input, calc_key_len(input));
	value = append_str(ft_strdup(""), pos_of_eq + 1, ft_strlen(pos_of_eq - 1));
	if (key == NULL || value == NULL)
		result = 1;
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
		return (1);
	tmp_entry->key = ft_strdup(key);
	tmp_entry->value = ft_strdup(value);
	tmp_node = ft_lstnew(tmp_entry);
	if (tmp_entry->key == NULL || tmp_entry->value == NULL || tmp_node == NULL)
	{
		free(tmp_entry->key);
		free(tmp_entry->value);
		free(tmp_entry);
		ft_lstclear(&tmp_node, free_dict_entry);
		return (1);
	}
	ft_lstadd_back(env, tmp_node);
	return (0);
}

int	update_env(t_list **env, char *key, char *val, t_env_mode update_mode)
{
	t_dict_entry	*current;

	if (env == NULL || key == NULL)
		return (1);
	current = get_value_by_key(*env, key);
	if (current != NULL)
	{
		if (update_mode == ENV_APPEND_VAR)
		{
			current->value = append_str(current->value, val, ft_strlen(val));
			if (current->value == NULL)
				return (1);
		}
		else
		{
			free(current->value);
			current->value = ft_strdup(val);
			if (current->value == NULL)
				return (1);
		}
	}
	else if (append_to_env(env, key, val))
		return (1);
	ft_lstsort(env, cmp_dict_entry_on_key);
	return (0);
}
