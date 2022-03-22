#include "minishell.h"

static char	update_mode_for_type(const char *input, char mode, char quote_type)
{
	if (mode == 0 && *input == quote_type && ft_strchr(input + 1, quote_type))
	{
		if (quote_type == SINGLE_QUOTE)
			return (SINGLE_QUOTE);
		else
			return (DOUBLE_QUOTE);
	}
	else if (*input == mode)
		return (NOT_IN_QUOTE);
	return (mode);
}

char	update_mode(const char *input, char mode)
{
	char	res;

	res = update_mode_for_type(input, mode, SINGLE_QUOTE);
	if (res)
	{
		return (res);
	}
	return (update_mode_for_type(input, mode, DOUBLE_QUOTE));
}

char	*trim_result(char *result)
{
	char	*tmp;

	if (result == NULL)
		return (NULL);
	tmp = result;
	result = ft_strtrim(result, " \n\t");
	free(tmp);
	return (result);
}

t_token	determine_redirection_type(t_string_slice *sub, t_list *current_cmd)
{
	t_token	result;

	result = EMPTY;
	if (sub->src[sub->current] == '>')
	{
		result = REDIR_OUT_REPLACE;
		if (sub->src[sub->start + 1] == sub->src[sub->start])
			result = REDIR_OUT_APPEND;
		get_content(current_cmd)->outtoken = result;
	}
	else if (sub->src[sub->start] == '<')
	{
		result = REDIR_IN_FILE;
		if (sub->src[sub->start + 1] == sub->src[sub->start])
			result = REDIR_IN_HERE_DOC;
		get_content(current_cmd)->intoken = result;
	}
	return (result);
}