/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splice_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:06:39 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:06:40 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	move_cursor_behind_whitespace(t_string_slice *sub)
{
	while (char_under_cursor(*sub) && ft_isspace(char_under_cursor(*sub)))
		(sub->current)++;
	sub->start = sub->current;
}

int	move_cursor_behind_token(t_string_slice *sub)
{
	if ((char_under_cursor(*sub) == '<' || char_under_cursor(*sub) == '>') \
		&& char_under_cursor(*sub) == sub->src[sub->current + 1])
	{
		(sub->start)++;
		(sub->current)++;
	}
	(sub->start)++;
	(sub->current)++;
	if (char_under_cursor(*sub) == 0 \
		|| sub->src[sub->current - SPACE_FOR_NULLTERMIN] == 0 \
		|| is_token(char_under_cursor(*sub)))
		return (1);
	return (0);
}

t_string_slice	init_slice_at_start_of(char *input)
{
	t_string_slice	result;

	ft_bzero(&result, sizeof(t_string_slice));
	result.src = input;
	return (result);
}

char	char_under_cursor(t_string_slice in)
{
	return ((in).src[(in).current]);
}
