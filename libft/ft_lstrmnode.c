/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrmnode.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:26 by                   #+#    #+#             */
/*   Updated: 2022/02/05 11:34:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrmnode(t_list **lst, t_list *node_to_delete, void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (lst == NULL || node_to_delete == NULL)
		return ;
	prev = node_to_delete->prev;
	next = node_to_delete->next;
	ft_lstdelone(node_to_delete, del);
	if (*lst == node_to_delete)
		*lst = next;
	if (next != NULL)
		next->prev = prev;
	if (prev != NULL)
		prev->next = next;
}
