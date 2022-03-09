#include "../minishell.h"

char	**split_args(char *in)
{
	char	**result;

	result = malloc(sizeof(char *) * (3));
	if (! result)
		return (NULL);
	result[0] = NULL;
	return (result);
	(void) in;
}

static char _update_mode(char *input, char mode, char quote_type)
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

char update_mode(char *input, char mode)
{
	char res = _update_mode(input, mode, SINGLE_QUOTE);
	if (res)
	{
		return res;
	}
	return (_update_mode(input, mode, DOUBLE_QUOTE));
}

int count_substrings(char *in)
{
	int		i;
	int		nbr;
	char	mode;

	i = 0;
	nbr = 0;
	mode = 0;
	while (in[i])
	{
		while (in[i] && (in[i] != ' ' || mode != NOT_IN_QUOTE))
		{
			mode = update_mode(&in[i], mode);
			++i;
		}
		if (i)
			nbr++;
		while (in[i] && in[i] == ' ')
			i++;
	}
	return (nbr);
}