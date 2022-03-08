/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_digits_in_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:49:02 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	calc_digits_in_number(int in)
{
	int				result;
	unsigned int	tmp;

	tmp = in;
	result = 1;
	if (in < 0)
	{
		result++;
		tmp = -in;
	}
	while (tmp / 10 > 0)
	{
		result++;
		tmp = tmp / 10;
	}
	return (result);
}
