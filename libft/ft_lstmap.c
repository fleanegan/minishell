/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:06 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			advance_pointer(t_list **orig_lst);

static t_list		*copy_content_into_new_struct(const t_list *orig_lst,
						void *(*cpy_fun)(void *), t_list *cpy_curent_pos);

t_list	*ft_lstmap(t_list *orig_lst, void *(*cpy_fun)(void *),
			void (*del)(void *))

{
	t_list	*cpy_curent_pos;
	t_list	*new_lst;

	new_lst = NULL;
	while (orig_lst)
	{
		cpy_curent_pos = copy_content_into_new_struct(orig_lst, cpy_fun,
				cpy_curent_pos);
		if (! cpy_curent_pos)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		advance_pointer(&orig_lst);
		ft_lstadd_back(&new_lst, cpy_curent_pos);
	}
	return (new_lst);
}

t_list	*copy_content_into_new_struct(const t_list *orig_lst,
			void *(*cpy_fun)(void *), t_list *cpy_curent_pos)
{
	cpy_curent_pos = ft_lstnew(NULL);
	if (! cpy_curent_pos)
		return (NULL);
	cpy_curent_pos->content = cpy_fun(orig_lst->content);
	return (cpy_curent_pos);
}

void	advance_pointer(t_list **orig_lst)
{
	*orig_lst = (*orig_lst)->next;
}
