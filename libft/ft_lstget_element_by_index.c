/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_element_by_index_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:54 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_element_by_index(t_list *lst, size_t index)
{
	while (index-- > 0)
	{
		if (lst)
			lst = lst->next;
		else
			return (NULL);
	}
	return (lst);
}

	t_list	*ft_lstget_element_by_function(t_list *lst, \
int (*equals)(void *, int), int i)
{
	while (lst)
	{
		if (equals(lst->content, i))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
