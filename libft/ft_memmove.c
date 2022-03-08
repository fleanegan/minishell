/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:17 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src_ptr;
	unsigned char	*dest_ptr;

	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		src_ptr = (unsigned char *) src + n - 1;
		dest_ptr = (unsigned char *) dest + n - 1;
		while (n--)
		{
			*dest_ptr-- = *src_ptr--;
		}
	}
	return (dest);
}
