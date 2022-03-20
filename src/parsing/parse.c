#include "minishell.h"

t_list	*parse(char *input, t_list *env)
{
	t_list			*result_cmd;
	t_string_slice	current_substr;

	current_substr = init_slice_at_start_of(input);
	result_cmd = NULL;
	move_cursor_behind_whitespace(&current_substr);
	while (current_substr.src[current_substr.current] != 0)
	{
		if (parse_one_command(&current_substr, &result_cmd, env))
		{
			free(input);
			input = NULL;
			return (free_list_and_return_null(&result_cmd, free_cmd));
		}
	}
	free(input);
	input = NULL;
	if (result_cmd != NULL \
		&& get_content(ft_lstlast(result_cmd))->outtoken == PIPE)
		return (free_list_and_return_null(&result_cmd, free_cmd));
	return (result_cmd);
}

int	parse_one_command(t_string_slice *sub, t_list **result_cmd, t_list *env)
{
	t_list	*current_cmd;
	t_list	*arg_tmp;

	arg_tmp = NULL;
	append_new_cmd(result_cmd, &current_cmd);
	append_new_arg(&arg_tmp, ft_strdup(""));
	while (char_under_cursor(*sub) && char_under_cursor(*sub) != '|')
		if (parse_next_attribute(env, current_cmd, &arg_tmp, sub))
			return (free_list_and_return_null(&arg_tmp, free) == NULL);
	(get_content(current_cmd))->args = (char **) to_array(arg_tmp, cpy_str);
	if ((sub->src[sub->start] == '|' && parse_pipe(sub, current_cmd)) \
		|| get_content(current_cmd)->exec_name == NULL)
		return (free_list_and_return_null(&arg_tmp, free) == NULL);
	ft_lstclear(&arg_tmp, free);
	return (0);
}

int	parse_next_attribute(\
	t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *sub)
{
	t_list	*current_arg;

	if (is_token(char_under_cursor(*sub)) && \
		parse_redirection(env, current_cmd, sub))
		return (1);
	else if (get_content(current_cmd)->exec_name == NULL)
	{
		(get_content(current_cmd)->exec_name) = parse_until(sub, ft_isspace);
		if (get_content(current_cmd)->exec_name == NULL)
			return (1);
	}
	else if (is_token(char_under_cursor(*sub)) == 0 \
		&& append_next_argument_to_list(arg_tmp, sub, &current_arg))
		return (1);
	return (0);
}

int	append_next_argument_to_list(\
	t_list **arg_tmp, t_string_slice *sub, t_list **current_arg)
{
	char	*tmp_arg_content;
	int		cursor_before_parse;

	cursor_before_parse = sub->current;
	tmp_arg_content = parse_until(sub, ft_isspace);
	if (sub->current == cursor_before_parse)
		return (0);
	if (tmp_arg_content == NULL)
		return (1);
	(*current_arg) = ft_lstnew(tmp_arg_content);
	if ((*current_arg) == NULL)
	{
		free(tmp_arg_content);
		return (1);
	}
	ft_lstadd_back(arg_tmp, (*current_arg));
	return (0);
}

char	*parse_until(t_string_slice *sub, int (*stop_condition)(int))
{
	char	*result;
	char	mode;

	mode = 0;
	move_cursor_behind_whitespace(sub);
	while (sub->src[(sub->current)])
	{
		mode = update_mode((char *)&sub->src[sub->current], mode);
		if (mode == NOT_IN_QUOTE \
			&& (is_token(sub->src[(sub->current)]) \
				|| stop_condition(sub->src[(sub->current)])))
			break ;
		(sub->current)++;
	}
	if (sub->start > sub->current - 1)
		return (NULL);
	result = append_str(ft_strdup(""), \
	(char *)&sub->src[sub->start], sub->current - sub->start);
	move_cursor_behind_whitespace(sub);
	delete_quotes(result);
	return (trim_result(result));
}
