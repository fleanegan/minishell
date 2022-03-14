/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:32 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_no_integer_overflow(unsigned long bytes_needed);

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned long	bytes_needed;
	void			*result;

	if (! size || ! nmemb)
	{
		result = malloc(1);
		ft_bzero(result, 1);
		if (! result)
			return (NULL);
		*(int *) result = 0;
		return (result);
	}
	bytes_needed = nmemb * size;
	if (bytes_needed > 0 && is_no_integer_overflow(bytes_needed))
	{
		result = malloc(bytes_needed);
		if (!result)
			return (NULL);
		ft_bzero(result, bytes_needed);
		return (result);
	}
	return (NULL);
}

static int	is_no_integer_overflow(unsigned long bytes_needed)
{
	return (bytes_needed < 2147483648);
}
