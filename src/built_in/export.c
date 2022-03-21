#include "minishell.h"

int export(t_list *env, char *key)
{
	(void) env;
	(void) key;
	char **key_split;
	t_dict_entry	*current;

	key_split = ft_split(key, '=');
	printf("%s, %s\n", key_split[0], key_split[1]);
	current = get_value_by_key(env, key_split[0]);
	if (current == NULL)
		append_to_dict(&env, key_split[0], key_split[1]);
	else
	{
		puts("test");
		free(current->value);
		current->value = ft_strdup(key_split[1]);
	}
	free_2d_array((void **) key_split);
	return 0;
}