#include "../minishell.h"

static char update_mode_for_type(char *input, char mode, char quote_type)
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
	char res = update_mode_for_type(input, mode, SINGLE_QUOTE);
	if (res)
	{
		return res;
	}
	return (update_mode_for_type(input, mode, DOUBLE_QUOTE));
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

char	**fill(char **dest, char *in)
{
	int		current;
	int		start;
	int		current_substring;
	char	mode;

	current = 0;
	start = 0;
	mode = 0;
	current_substring = 0;
	while (in[current])
	{
		while (in[current] && (in[current] != ' ' || mode != NOT_IN_QUOTE))
		{
			mode = update_mode(&in[current], mode);
			++current;
		}
		if (current != start)
		{
			dest[current_substring] = strdup_from_to(in, start, current - 1);
			if (! dest[current_substring])
			{
				free_2d_array((void **) dest);
				return (NULL);
			}
			current_substring++;
		}
		skip_whitespace(in, &start, &current);
	}
	return (dest);
}

char	**split_args(char *in)
{
	char	**result;
	size_t	alloc_size;

	alloc_size = count_substrings(in) \
					+ SPACE_FOR_NULLTERMIN \
					+ SPACE_FOR_EXEC_NAME;
	result = malloc(sizeof(char *) * (alloc_size));
	if (! result)
		return (NULL);
	result[0] = NULL;
	result[alloc_size - 1] = NULL;

	if (! fill(&result[1], in))
		return (NULL);
	return (result);
	(void) in;
}