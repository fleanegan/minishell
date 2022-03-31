#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../inc/minishell.h"
# include "../inc/minishell.h"
#include "../criterion-v2.3.3/include/criterion/assert.h"
#include "../criterion-v2.3.3/include/criterion/criterion.h"
#include "../criterion-v2.3.3/include/criterion/redirect.h"
# include <criterion/criterion.h>
# include <criterion/theories.h>
# include <criterion/redirect.h>
# include <ctype.h>
# include <string.h>
# include <limits.h>

int replacement_for_broken_criterion_stdout_matcher(char *compare_string, FILE *f_stream) {
	size_t read;
	char buf[1];
	size_t len = strlen(compare_string);
	size_t	ctr = 0;
	int matches = 1;

	while ((read = fread(buf, 1, sizeof(char), f_stream)) > 0) {
		ctr++;
		if (!compare_string || *buf != *compare_string++)
			matches = 0;
	}
	if (read)
		while (fread(buf, 1, sizeof (buf), f_stream) > 0) ctr++;
	if (len != ctr)
		matches = 0;
	return (matches);
}

void cr_bugfix_assert_str_stdout(char *compare_string)
{
	cr_assert(replacement_for_broken_criterion_stdout_matcher(compare_string, cr_get_redirected_stdout()));
}

void	print_cmd(t_list	*cmd)
{
	int	i;

	while (cmd != NULL)
	{
		printf("-----------------------------------------------------------\n");
		i = 0;
		printf("execname : %s\ninfile : %s\noutfile : %s\nintoken : %d\nouttoken : %d\npipe : %d\n", \
			get_content(cmd)->exec_name, get_content(cmd)->infile, \
			get_content(cmd)->outfile, get_content(cmd)->intoken, \
			get_content(cmd)->outtoken, get_content(cmd)->pipe);
		while (get_content(cmd)->args[i] != NULL)
		{
			printf("arg[%d] = %s\n", i, get_content(cmd)->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
	printf("-----------------------------------------------------------\n");
}


#endif	 // TEST_UTILS_H
