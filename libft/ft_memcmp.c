/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:13 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		calc_difference_of_current_bytes(const unsigned char *orig,
					const unsigned char *compare);
static void		advance_pointers(const unsigned char **orig,
					const unsigned char **compare);
static size_t	has_not_reached_end(size_t *n);

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*orig = s1;
	const unsigned char	*compare = s2;
	int					diff;

	if (!n)
		return (0);
	while (has_not_reached_end(&n))
	{
		diff = calc_difference_of_current_bytes(orig, compare);
		advance_pointers(&orig, &compare);
		if (diff)
			break ;
	}
	return (diff);
}

static size_t	has_not_reached_end(size_t *n)
{
	return ((*n)--);
}

static void	advance_pointers(const unsigned char **orig,
			const unsigned char **compare) {
	(*orig)++;
	(*compare)++;
}

static int	calc_difference_of_current_bytes(const unsigned char *orig,
		const unsigned char *compare) {
	return (*orig - *compare);
}
