/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:29 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_auxilliar.h"

int	ft_atoi(const char *in)
{
	short int	sign;
	long int	res;

	res = 0;
	sign = 1;
	while (ft_isspace(*in))
		in++;
	if (*in == '-' || *in == '+')
	{
		if (*in == '-')
			sign = -1;
		in++;
	}
	while (ft_isdigit(*in))
		res = 10 * res + (*in++ - '0');
	return (sign * (int) res);
}
