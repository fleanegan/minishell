/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_int.c 				                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:29 by                   #+#    #+#             */
/*   Updated: 2022/02/05 11:21:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*malloc_int(int in)
{
	int	*result;

	result = malloc (sizeof(int));
	*result = in;
	return (result);
}

unsigned long	*malloc_unsigned_long(unsigned long in)
{
	unsigned long	*result;

	result = malloc (sizeof(unsigned long));
	*result = in;
	return (result);
}
