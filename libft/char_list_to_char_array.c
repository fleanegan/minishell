/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_to_char_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:29 by                   #+#    #+#             */
/*   Updated: 2022/02/05 11:21:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*char_list_to_char_array(t_list *lst)
{
	char	*result;
	t_list	*tmp;
	int		ctr;

	if (! lst)
		return (NULL);
	result = malloc((SPACE_FOR_NULLTERMIN + ft_lstsize(lst)) * sizeof(char));
	if (! result)
		return (NULL);
	ctr = 0;
	tmp = lst;
	while (lst)
	{
		result[ctr] = *(char *)lst->content;
		if (! result[ctr])
			break ;
		ctr++;
		lst = lst->next;
	}
	ft_lstclear(&tmp, free);
	return (result);
}
