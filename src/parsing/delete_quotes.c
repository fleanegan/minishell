#include "../minishell.h"

char	*get_first_quote(char *in)
{
	char	*first_quote_simple;
	char	*first_quote_double;

	first_quote_simple = ft_strchr(in, SINGLE_QUOTE);
	first_quote_double = ft_strchr(in, DOUBLE_QUOTE);
	if (first_quote_double == NULL)
		return (first_quote_simple);
	if (first_quote_simple == NULL)
		return (first_quote_double);
	if (first_quote_simple < first_quote_double)
		return (first_quote_simple);
	return (first_quote_double);
}

char	*get_second_quote(const char *first_quote)
{
	char	*second_quote;

	if (*first_quote == SINGLE_QUOTE)
		second_quote = ft_strchr(first_quote + 1, SINGLE_QUOTE);
	else
		second_quote = ft_strchr(first_quote + 1, DOUBLE_QUOTE);
	return (second_quote);
}

void	remove_by_copying(char *first_quote, char *second_quote)
{
	if (*first_quote && *second_quote)
	{
		ft_strlcpy(first_quote, first_quote + 1, ft_strlen(first_quote) + 1);
		ft_strlcpy(second_quote - 1, second_quote, ft_strlen(second_quote) + 1);
	}
}

char	*delete_quotes(char *in)
{
	char	*first_quote;
	char	*second_quote;

	if (! in)
		return (NULL);
	first_quote = get_first_quote(in);
	if (first_quote == NULL)
		return (in);
	second_quote = get_second_quote(first_quote);
	if (second_quote == NULL)
	{
		ft_strlcpy(first_quote + 1, \
		delete_quotes(first_quote + 1), ft_strlen(first_quote) + 1);
		return (in);
	}
	remove_by_copying(first_quote, second_quote);
	ft_strlcpy(second_quote, \
	delete_quotes(second_quote), ft_strlen(second_quote) + 1);
	return (in);
}
