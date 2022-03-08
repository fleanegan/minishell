/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:44 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	translate_int_to_char_array(unsigned int n, char *result,
				int digits_to_hold_number);

static char	*allocate_memory_and_zero_init(char **result,
				int digits_to_hold_number);

static int	calc_digits_in_number(int in);

char	*ft_itoa(int n)
{
	char			*result;
	int				digits_to_hold_number;
	unsigned int	tmp;

	tmp = n;
	if (n < 0)
		tmp = -n;
	digits_to_hold_number = calc_digits_in_number(n);
	result = allocate_memory_and_zero_init(&result, digits_to_hold_number);
	if (! result)
		return (NULL);
	translate_int_to_char_array(tmp, result, digits_to_hold_number);
	if (n < 0)
		result[0] = '-';
	return (result);
}

static void	translate_int_to_char_array(unsigned int n, char *result,
			int digits_to_hold_number)
{
	int	current_index;

	current_index = digits_to_hold_number - SPACE_NULLTERMIN;
	if (! n)
		result[0] = '0';
	while (n > 0)
	{
		result[current_index--] = '0' + (n % 10);
		n = n / 10;
	}
}

static char	*allocate_memory_and_zero_init(char **result,
			int digits_to_hold_number)
{
	*result = malloc(sizeof(char) * (digits_to_hold_number
				+ SPACE_NULLTERMIN));
	if (!*result)
		return (NULL);
	ft_bzero(*result, digits_to_hold_number
		+ SPACE_NULLTERMIN);
	return (*result);
}

static int	calc_digits_in_number(int in)
{
	int				result;
	unsigned int	tmp;

	tmp = in;
	result = 1;
	if (! in)
		return (result);
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
