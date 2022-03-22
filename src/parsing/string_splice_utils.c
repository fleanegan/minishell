#include "../minishell.h"

void	move_cursor_behind_whitespace(t_string_slice *sub)
{
	if (sub->current)
		sub->start = sub->current;
	while (sub->src[sub->current] && ft_isspace(sub->src[sub->current]))
		(sub->current)++;
	sub->start = sub->current;
}

int	move_cursor_behind_token(t_string_slice *sub)
{
	if ((sub->src[sub->current] == '<' || sub->src[sub->current] == '>') \
		&& sub->src[sub->current] == sub->src[sub->current + 1])
	{
		(sub->start)++;
		(sub->current)++;
	}
	(sub->start)++;
	(sub->current)++;
	if (sub->src[sub->current] == 0 \
		|| sub->src[sub->current - SPACE_FOR_NULLTERMIN] == 0 \
		|| is_token(sub->src[sub->current]))
		return (1);
	return (0);
}

t_string_slice	init_slice_at_start_of(const char *input)
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
