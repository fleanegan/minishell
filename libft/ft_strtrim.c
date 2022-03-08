/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:39 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_auxilliar.h"

static int		is_only_composed_of_set(const char *set, char *s1);

size_t	count_leading_trimmable(const char *src, const char *set)
{
	size_t	result;

	result = 0;
	while (*src && is_char_in_set(*src, set))
	{
		result++;
		src++;
	}
	return (result);
}

size_t	count_trailing_trimmable(const char *src, const char *set)
{
	size_t	result;

	result = 0;
	while (*src)
		src++;
	src--;
	while (*src && is_char_in_set(*src, set))
	{
		result++;
		src--;
	}
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	leading_trash;
	size_t	trailing_trash;
	size_t	len_trimmed;
	int		pure_set;

	if (!s1)
		return (NULL);
	pure_set = is_only_composed_of_set(set, (char *)s1);
	if (pure_set)
		return (ft_strdup(""));
	leading_trash = count_leading_trimmable(s1, set);
	trailing_trash = count_trailing_trimmable(s1, set);
	len_trimmed = ft_strlen(s1) - leading_trash - trailing_trash;
	return (ft_substr(s1, leading_trash, len_trimmed));
}

int	is_only_composed_of_set(const char *set, char *s1)
{
	int		pure_set;
	char	*tmp;

	tmp = s1;
	pure_set = 1;
	while (*tmp)
	{
		if (!ft_strchr(set, *tmp))
		{
			pure_set = 0;
			break ;
		}
		tmp++;
	}
	return (pure_set);
}
