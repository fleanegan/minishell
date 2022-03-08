/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:41 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	calc_required_memory_size(unsigned int start, size_t len,
			size_t len_src);

char	*generate_freable_pointer(char **result);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	len_src;
	size_t	size_allocated;

	if (!s)
		return (NULL);
	len_src = ft_strlen(s);
	if (start > len_src)
		return (generate_freable_pointer(&result));
	size_allocated = calc_required_memory_size(start, len, len_src);
	result = malloc(sizeof(char) * (size_allocated + SPACE_NULLTERMIN));
	if (! result)
		return (NULL);
	ft_bzero(result, size_allocated);
	s += start;
	ft_strlcpy(result, s, size_allocated + SPACE_NULLTERMIN);
	return (result);
}

char	*generate_freable_pointer(char **result)
{
	*result = malloc(1);
	if (!*result)
		return (NULL);
	**result = 0;
	return (*result);
}

size_t	calc_required_memory_size(unsigned int start, size_t len,
			size_t len_src)
{
	size_t	size_allocated;

	if (len < (len_src - start))
		size_allocated = len;
	else
		size_allocated = len_src - start;
	return (size_allocated);
}
