/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:07 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstnullterminate(t_list *lst)
{
	lst->next = NULL;
	lst->prev = NULL;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	result = (t_list *) malloc(sizeof(t_list));
	if (!result)
		return (NULL);
	result->content = content;
	ft_lstnullterminate(result);
	return (result);
}
