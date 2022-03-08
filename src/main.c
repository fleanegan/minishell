#include "minishell.h"

#ifndef IS_TEST

int	main(int argc, char **argv)
{
	char *result = readline("rocammadour>>:");
	printf("testmeee: %s\n", result);
	return (0);
	(void) argc;
	(void) argv;
}

#endif
