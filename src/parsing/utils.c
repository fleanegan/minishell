#include "minishell.h"

void move_start_and_end_behind_whitespace(t_string_slice *sub)
{
	if (sub->current)
		sub->start = sub->current;
	while (sub->src[sub->current] && ft_isspace(sub->src[sub->current]))
		(sub->current)++;
	sub->start = sub->current;
}

char	*strdup_from_to(t_string_slice sub)
{
	char 	*res;
	int		i;

	if (sub.src == NULL || sub.start > sub.current - 1)
		return (NULL);
	res = malloc((\
			sub.current - sub.start + SPACE_FOR_NULLTERMIN) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (sub.start <= sub.current - 1)
	{
		res[i] = sub.src[sub.start];
		i++;
		sub.start++;
	}
	res[i] = '\0';
	return (res);
}

static char update_mode_for_type(const char *input, char mode, char quote_type)
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

char update_mode(const char *input, char mode)
{
	char res = update_mode_for_type(input, mode, SINGLE_QUOTE);
	if (res)
	{
		return res;
	}
	return (update_mode_for_type(input, mode, DOUBLE_QUOTE));
}

int is_token(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

char *trim_result(char *result)
{
	char    *tmp;

	tmp = result;
	result = ft_strtrim(result, " \n\t");
	free(tmp);
	return (result);
}
