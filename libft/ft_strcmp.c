/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:26 by                   #+#    #+#             */
/*   Updated: 2022/02/05 11:34:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_auxilliar.h"

int	calc_strnlen_size(char *s1, char *s2)
{
	return ((int) calc_max_unsigned(\
		ft_strlen(s1), \
		ft_strlen(s2)));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	max;

	max = calc_strnlen_size(s1, s2);
	return (ft_strncmp(s1, s2, max));
}
