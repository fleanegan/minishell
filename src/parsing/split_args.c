#include "../minishell.h"

int	calc_end_of_sub(char *in, int current);

int	count_substrings(char *in)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (in[i])
	{
		i = calc_end_of_sub(in, i);
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

	current = 0;
	start = 0;
	current_substring = 0;
	while (in[current])
	{
		current = calc_end_of_sub(in, current);
		if (current != start)
		{
			dest[current_substring] = strdup_from_to(in, start, current - 1);
			if (! dest[current_substring])
				return (free_2d_array((void **) dest));
			current_substring++;
		}
		skip_whitespace(in, &start, &current);
	}
	return (dest);
}

int	calc_end_of_sub(char *in, int current)
{
	static char	mode;

	while (in[current] && (in[current] != ' ' || mode != NOT_IN_QUOTE))
	{
		mode = update_mode(&in[current], mode);
		++current;
	}
	return (current);
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
	result[0] = ft_strdup("");
	if (result[0] == NULL)
		return (NULL);
	result[alloc_size - 1] = NULL;
	if (fill(&result[1], in) == NULL)
		return (NULL);
	return (result);
}
