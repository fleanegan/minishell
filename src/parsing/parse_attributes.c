#include "../minishell.h"

char	*parse_until(t_string_slice *sub, int(*stop_condition)(int))
{
	char    *result;
	char    mode;

	mode = 0;
	move_cursor_behind_whitespace(sub);
	while (sub->src[(sub->current)])
	{
		mode = update_mode((char *)&sub->src[sub->current], mode);
		if (mode == NOT_IN_QUOTE && (is_token(sub->src[(sub->current)]) || stop_condition(sub->src[(sub->current)])))
			break ;
		(sub->current)++;
	}
	result = strdup_from_to(*sub);
	move_cursor_behind_whitespace(sub);
	delete_quotes(result);
	return (trim_result(result));
}

int append_next_argument_to_list(t_list **arg_tmp, t_string_slice *sub, t_list **tmp_arg) {
	char	*tmp_arg_content;
	int		cursor_before_parse;

	cursor_before_parse = sub->current;
	tmp_arg_content = parse_until(sub, ft_isspace);
	if (sub->current == cursor_before_parse)
		return (0);
	if (tmp_arg_content == NULL)
		return (1);
	(*tmp_arg) = ft_lstnew(tmp_arg_content);
	if ((*tmp_arg) == NULL)
	{
		free(tmp_arg_content);
		return (1);
	}
	ft_lstadd_back(arg_tmp, (*tmp_arg));
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