#include "../minishell.h"

char	*parse_until(t_string_slice *sub, int(*stop_condition)(int))
{
	char    *result;
	char    mode;

	mode = 0;
	move_start_and_end_behind_whitespace(sub);
	while (sub->src[(sub->current)])
	{
		mode = update_mode((char *)&sub->src[sub->current], mode);
		if (mode == NOT_IN_QUOTE && (is_token(sub->src[(sub->current)]) || stop_condition(sub->src[(sub->current)])))
			break ;
		(sub->current)++;
	}
	result = strdup_from_to(*sub);
	move_start_and_end_behind_whitespace(sub);
	return (trim_result(result));
}


int parse_token(t_string_slice *sub, t_list *current_cmd, t_list *env)
{
	move_start_and_end_behind_whitespace(sub);
	//if (get_content(current_cmd)->exec_name == NULL)
	//	return (1);
	if (is_token(sub->src[(sub->start)]))
	{
		if (sub->src[sub->start] == '|')
		{
			if (parse_pipe(sub, current_cmd))
				return (1);
			return (0);
		}
		else if (sub->src[sub->start] == '>' && parse_redir_out(sub, current_cmd, env))
			return (1);
		else if (sub->src[sub->start] == '<' && parse_redir_in(sub, current_cmd, env))
			return (1);
	}
	move_start_and_end_behind_whitespace(sub);
	return (0);
}

int parse_args(t_string_slice *sub, t_list *current_cmd)
{
	char    *unsplit_result;
	char    **tmp;

	unsplit_result = parse_until(sub, is_token);
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
int parse_exec_name(t_string_slice *sub, t_list *current_cmd)
{
	get_content(current_cmd)->exec_name = parse_until( \
                sub, ft_isspace);
	if (current_cmd == NULL || get_content(current_cmd)->exec_name == NULL) {
		return (1);
	}
	delete_quotes(get_content(current_cmd)->exec_name);
	return (0);
}