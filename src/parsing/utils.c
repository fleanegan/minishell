#include "minishell.h"

void	remove_by_copying(char *first_quote, char *second_quote)
{
	if (*first_quote && *second_quote)
	{
		ft_strlcpy(first_quote, first_quote + 1, ft_strlen(first_quote) + 1);
		ft_strlcpy(second_quote - 1, second_quote, ft_strlen(second_quote) + 1);
	}
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

int	is_token(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	cpy_str(void *content, void **result)
{
	(*result) = ft_strdup((char *)content);
	if (*result == NULL)
		return (1);
	return (0);
}
