/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_compare.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:03:02 by                   #+#    #+#             */
/*   Updated: 2021/12/03 11:32:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcompare(t_list *a, t_list *b, int (*compare)(void *, void *))
{
	if (! a || !b)
		return (0);
	while (a && b)
	{
		if (! compare(a->content, b->content))
			return (0);
		a = a->next;
		b = b->next;
	}
	if (a || b)
		return (0);
	return (1);
}
