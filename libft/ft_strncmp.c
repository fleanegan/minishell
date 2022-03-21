/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:36 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_min_unsigned(size_t a, size_t b);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	max_n;

	if (s1 == NULL || s2 == NULL)
		return (1);
	max_n = calc_min_unsigned(n, ft_strlen(s1) + SPACE_NULLTERMIN);
	max_n = calc_min_unsigned(max_n, ft_strlen(s2) + SPACE_NULLTERMIN);
	return (ft_memcmp(s1, s2, max_n));
}

size_t	calc_min_unsigned(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	calc_max_unsigned(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}
