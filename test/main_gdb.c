# include "../src/minishell.h"

void	ft_lstput_env(t_list *lst)
{
	while (lst)
	{
		ft_putstr_fd(((t_dict_entry *)lst->content)->key, STDOUT_FILENO);
		lst = lst->next;
	}
}

int main()
{
	t_list *env = NULL;
	char *envp[] = {"test=test", "Test=test", "Ab=test", "abc=test", "ab1=test", "abd=test", "aba=test", NULL};
	env = init(envp);

	ft_lstput_env(env);
	printf("first: %s\n", ((t_dict_entry *)env->content)->key);
	msh_env(&env, NULL, 0);
	char *in = ft_strdup("regular $?$V2");
	char *result = expand_one_layer_of_variables(env, in);
	printf("res: %s\n", result);
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
	return 0;
}