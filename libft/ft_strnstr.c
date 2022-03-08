/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:37 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_of_needle;

	if (!ft_strlen(needle))
		return ((char *)(haystack));
	len_of_needle = ft_strlen(needle);
	while (len >= len_of_needle && *haystack)
	{
		if (!ft_strncmp(haystack, needle, len_of_needle))
			return ((char *) haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
