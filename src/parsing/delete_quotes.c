/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:03:48 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:03:51 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
