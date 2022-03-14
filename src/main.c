#include "minishell.h"

#ifndef IS_TEST

int	main(void)
{
	//char	*result;
	t_list	*env;

	env = init();
	if (env == NULL)
		return (1);
	char	*in = ft_strdup("$ ");
	//printf("[%s]\n", get_value_by_key(env, "PATH")->value);
	printf("[%s]\n", expand_variables(env, in));
/*	while (42)
	{
		result = readline("minishell$");
		if (! result)
		{
			handle_ctrl_d(-1, NULL, NULL);
			return (0);
		}
		add_history(result);
		execution(result, NULL, NULL);
	}
*/
	return (0);
}

#endif
