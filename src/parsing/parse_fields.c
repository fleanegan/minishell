#include "../minishell.h"

char	*parse_until(const char *input, int *start, int *current, int(*stop_condition)(int))
{
	char    *result;
	char    mode;

	mode = 0;
	skip_whitespace(input, start, current);
	while (input[(*current)])
	{
		mode = update_mode((char *)&input[*current], mode);
		if (mode == NOT_IN_QUOTE && stop_condition(input[(*current)]))
			break ;
		// expand env vars here
		(*current)++;
	}
	result = strdup_from_to(input, (*start), (*current) - 1);
	return (trim_result(result));
}

int	parse_token(const char *in, int *start, int *current, t_list *current_cmd)
{
	skip_whitespace(in, start, current);
	if (is_end_of_arg(in[(*start)]))
	{
		(*start)++;
		(*current)++;
	}
	return (0);
	(void) current_cmd;
}

int parse_args( \
		const char *input, t_list *current_cmd, int *start, int *current)
{
	char    *unsplit_result;
	char    **tmp;

	unsplit_result = parse_until( input, start, current, is_end_of_arg);
	get_content(current_cmd)->args = split_args(unsplit_result);
	if (*get_content(current_cmd)->args == NULL)
	{
		free(unsplit_result);
		return (1);
	}
	tmp = get_content(current_cmd)->args;
	while (*tmp)
	{
		delete_quotes(*tmp);
		tmp++;
	}
	return (0);
}

// protect malloc!
int	parse_exec_name(const char *input, \
	t_list *current_cmd, int *start, int *current)
{
	get_content(current_cmd)->exec_name = parse_until( \
                input, start, current, ft_isspace);
	if (get_content(current_cmd)->exec_name == NULL)
		return (1);
	delete_quotes(get_content(current_cmd)->exec_name);
	return (0);
}