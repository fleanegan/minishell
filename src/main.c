#include "minishell.h"

#ifndef IS_TEST

int	main(void)
{
	char	*result;
	t_list	*env;

	env = init();
	if (env == NULL)
		return (1);
	while (42)
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
}

#endif
