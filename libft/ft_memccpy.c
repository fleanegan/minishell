/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:11 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*addr_of_key_in_src;
	size_t			bytes_to_copy;

	if (!src)
		return (NULL);
	addr_of_key_in_src = ft_memchr(src, (unsigned char) c, n);
	if (!addr_of_key_in_src)
	{
		ft_memcpy(dest, src, n);
		return (NULL);
	}
	bytes_to_copy = addr_of_key_in_src - (unsigned char *) src + 1;
	ft_memcpy(dest, src, bytes_to_copy);
	return (dest + bytes_to_copy);
}
