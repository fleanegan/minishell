/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_element_at_index_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:49 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_element_at_index(t_list **lst, t_list *new, size_t index)
{
	t_list	*next;
	t_list	*tmp;

	if (index == 0)
	{
		ft_lstadd_front(lst, new);
		return (0);
	}
	if (! lst)
		return (-1);
	tmp = ft_lstget_element_by_index(*lst, index - 1);
	if (! tmp)
		return (-1);
	next = tmp->next;
	if (next)
	{
		new->prev = next->prev;
		next->prev = new;
	}
	tmp->next = new;
	new->next = next;
	return (0);
}
