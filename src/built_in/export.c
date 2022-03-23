#include "minishell.h"

int msh_export(t_list *env, t_cmd *cmd)
{
	puts("implement export..");
	return (0);
	(void) cmd;
	(void) env;
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
	return 0;
}
