# include "../src/minishell.h"

int main()
{
	t_list *env = init();
	update_env(&env, "?", "TEST", ENV_REPLACE_VAR);
	update_env(&env, "V2", "ME", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $?$V2");
	char *result = expand_one_layer_of_variables(env, in);
	printf("res: %s\n", result);
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
	return 0;
}