#include "minishell.h"

#ifndef IS_TEST

int	main(void)
{
	char *result;
	if (init())
		return (1);
	while (42)
	{
		result = readline("minishell$");
		if (! result)
		{
			handle_ctrl_d(-1, NULL, NULL);
			return (0);
		}
		execution(result, NULL, NULL);
	}
	return (0);
}

#endif
