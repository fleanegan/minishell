/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:38 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	reached_max_count(size_t *n)
{
	int	is_not_found;

	is_not_found = !*n;
	(*n)--;
	return (is_not_found);
}

static void	*ft_memrchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *) s;
	while (*str != (unsigned char )c)
	{
		if (reached_max_count(&n))
			return (NULL);
		str--;
	}
	return (str);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	s += len;
	return (ft_memrchr(s, c, len));
}
