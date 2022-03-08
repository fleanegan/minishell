/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_until_first_set_char.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:50 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_auxilliar.h"

size_t	calc_len_sub_str(const char *src, const char *set)
{
	size_t	result;

	result = 0;
	while (*src && ! is_char_in_set(*src++, set))
		result++;
	return (result);
}
