/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:28 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	bytes_for_string;
	char	*result;

	if (s == NULL)
		return (NULL);
	bytes_for_string = ft_strlen(s) + SPACE_NULLTERMIN;
	result = malloc(sizeof(char) * bytes_for_string);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, bytes_for_string);
	return (result);
}
