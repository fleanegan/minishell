#include "minishell.h"


t_list *parsing(const char *input)
{
	t_list  *result_cmd;
	t_list  *current_cmd;
	int     start;
	int     current;

	current = 0;
	start = 0;
	result_cmd = NULL;
	while (input[start])
	{
		if ( append_new_cmd(&result_cmd, &current_cmd) \
			|| parse_exec_name(input, current_cmd, &start, &current) \
			|| parse_args(input, current_cmd, &start, &current) \
			|| parse_token(input, &start, &current, current_cmd))
		{
			ft_lstclear(&result_cmd, free_cmd);
			return (NULL);
		}
	}
	return (result_cmd);
}
