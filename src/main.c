#include "minishell.h"

#ifndef IS_TEST

int	main(void)
{
	char *result;

	while (42)
	{
		result = readline("minishell$");
		execution(result, NULL, NULL);
	}
	return (0);
}

#endif
