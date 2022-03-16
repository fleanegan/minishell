#include "minishell.h"


t_list *parsing(char *input)
{
	t_list  		*result_cmd;
	t_list  		*current_cmd;
	t_string_slice	current_substr;

	ft_bzero(&current_substr, sizeof(current_substr));
	current_substr.src = input;
	result_cmd = NULL;
	while (input[current_substr.start])
	{
		if (append_new_cmd(&result_cmd, &current_cmd) \
 			|| parse_exec_name(&current_substr, current_cmd) \
 			|| parse_args(&current_substr, current_cmd) \
 			|| parse_token(&current_substr, current_cmd))
		{
			puts("clearing list");
			ft_lstclear(&result_cmd, free_cmd);
			free(input);
			return (NULL);
		}
	}
	free(input);
	return (result_cmd);
}
