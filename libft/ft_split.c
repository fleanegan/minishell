/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <frederik.schlueter@posteo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:15:29 by fschlute          #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_sub_string_len(char const *str, char charset)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		while (str[i] && str[i] != charset)
			++i;
		if (i)
			nbr++;
		while (str[i] && str[i] == charset)
			i++;
	}
	return (nbr);
}

static int	fill(char **res, char *str, int len, char charset)
{
	int	i;
	int	ctr;

	i = -1;
	ctr = 0;
	while (++i < len)
	{
		while (*str && *str == charset)
			str++;
		while (str[ctr] && str[ctr] != charset)
			ctr++;
		if (!ctr)
			continue ;
		res[i] = (char *) malloc(sizeof(char) * (ctr + 1));
		if (! res[i])
			return (0);
		ft_strlcpy(res[i], str, ctr + 1);
		str += ctr;
		while (*str && *str == charset)
			str++;
		ctr = 0;
	}
	res[len] = 0;
	return (1);
}

char	**ft_split(char const *str, char charset)
{
	int		len;
	char	**res;

	if (! str)
		return (NULL);
	len = calc_sub_string_len((char *)str, charset);
	res = (char **) malloc(sizeof(char *) * (len + 1));
	if (! res)
	{
		free_2d_array((void **)res);
		return (NULL);
	}
	if (! fill(res, (char *)str, len, charset))
		return (NULL);
	return (res);
}
