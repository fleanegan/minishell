#include "../minishell.h"

int	calc_end_of_sub(const char *in, int current)
{
	static char	mode;

	while (in[current] && (in[current] != ' ' || mode != NOT_IN_QUOTE))
	{
		mode = update_mode(&in[current], mode);
		++current;
	}
	return (current);
}

int	split_count_substrings(char *in)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	if (in == NULL)
		return (0);
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
	t_string_slice	sub;
	int				current_substring;

	ft_bzero(&sub, sizeof(sub));
	sub.src = in;
	if (sub.src == NULL)
		return (NULL);
	current_substring = 0;
	while (sub.src[sub.current])
	{
		sub.current = calc_end_of_sub(sub.src, sub.current);
		if (sub.current != sub.start)
		{
			dest[current_substring] = strdup_from_to(sub);
			if (! dest[current_substring])
				return (free_2d_array((void **) dest));
			current_substring++;
		}

		move_start_and_end_behind_whitespace(&sub);
	}
	return (dest);
}

char	**split_args(char *in)
{
	char	**result;
	size_t	alloc_size;

	alloc_size = split_count_substrings(in) \
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
		return (result);
	return (result);
}
