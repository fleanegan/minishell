#include "../minishell.h"

char	*parse_until(const char *input, int *start, int *current, int(*stop_condition)(int))
{
	char    *result;
	char    mode;

	mode = 0;
	move_start_and_end_behind_whitespace(input, start, current);
	while (input[(*current)])
	{
		mode = update_mode((char *)&input[*current], mode);
		if (mode == NOT_IN_QUOTE && (is_token(input[(*current)]) || stop_condition(input[(*current)])))
			break ;
		(*current)++;
	}
	result = strdup_from_to(input, (*start), (*current));
	move_start_and_end_behind_whitespace(input, start, current);
	return (trim_result(result));
}


int	parse_token(const char *in, int *start, int *current, t_list *current_cmd)
{
	move_start_and_end_behind_whitespace(in, start, current);
	if (get_content(current_cmd)->exec_name == NULL)
		return (1);
	if (is_token(in[(*start)]))
	{
		if (in[*start] == '|')
		{
			if (parse_pipe(in, start, current, current_cmd))
				return (1);
			return (0);
		}
		else if (in[*start] == '>' && parse_redir_out(in, start, current, current_cmd))
			return (1);
		else if (in[*start] == '<' && parse_redir_in(in, start, current, current_cmd))
			return (1);
	}
	return (0);
}

int parse_args( \
		const char *input, t_list *current_cmd, int *start, int *current)
{
	char    *unsplit_result;
	char    **tmp;

	unsplit_result = parse_until(input, start, current, is_token);
	get_content(current_cmd)->args = split_args(unsplit_result);
	free(unsplit_result);
	if (*get_content(current_cmd)->args == NULL)
		return (1);
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
	if (current_cmd == NULL || get_content(current_cmd)->exec_name == NULL) {
		return (1);
	}
	delete_quotes(get_content(current_cmd)->exec_name);
	return (0);
}