#include "minishell.h"
#define SPACE_FOR_EQUAL_SIGN 1

int msh_export(t_list *env, t_cmd *cmd)
{
	char	*key;
	char	*value;
	char	*pos_of_eq;
	char	*input;
	int		result;

	result = 0;
	if (cmd == NULL || 	cmd->args[0] == NULL)
		return (1);
	input = cmd->args[1];
	pos_of_eq = ft_strchr(input, '=');
	if (pos_of_eq == NULL || pos_of_eq[1] == 0)
		return (result);
	if (calc_key_len(input) != pos_of_eq - input - SPACE_FOR_EQUAL_SIGN)
		return (1);
	key = append_str(ft_strdup(""), input, pos_of_eq - input);
	value = append_str(ft_strdup(""), pos_of_eq + 1, \
			ft_strlen(pos_of_eq - 1));
	if (key == NULL || value == NULL)
		result = 1;
	if (result == 0 && update_env(&env, key, value))
		result = 1;
	free(key);
	free(value);
	return (result);
}

// TODO: malloc protection
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

int update_env(t_list **env, char *key, char *value)
{
	(void) env;
	(void) key;
	t_dict_entry	*current;

	if (env == NULL || key == NULL)
		return (1);
	current = get_value_by_key(*env, key);
	if (current == NULL)
		append_to_dict(env, key, value);
	else
	{
		free(current->value);
		// TODO: malloc protection
		current->value = ft_strdup(value);
	}
	return (0);
}
