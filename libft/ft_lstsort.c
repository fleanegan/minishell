/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c 			                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:29 by                   #+#    #+#             */
/*   Updated: 2022/02/05 11:21:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_auxilliar.h"

static t_list	*init(t_list *const *lst);
void			swap(t_list *begin_of_comparison, t_list *current);

void	ft_lstsort(t_list **lst, int (*comp_func)(void *, void *))
{
	t_list	*tmp;
	t_list	*begin_of_comparison;

	begin_of_comparison = init(lst);
	while (begin_of_comparison && begin_of_comparison->next)
	{
		tmp = begin_of_comparison->next;
		while (tmp)
		{
			if (! comp_func(begin_of_comparison->content, tmp->content))
			{
				swap(begin_of_comparison, tmp);
			}
			tmp = tmp->next;
		}
		begin_of_comparison = begin_of_comparison->next;
	}
}

t_list	*init(t_list *const *lst)
{
	t_list	*begin_of_comparison;

	begin_of_comparison = NULL;
	if (lst && *lst)
		begin_of_comparison = *lst;
	return (begin_of_comparison);
}

void	swap(t_list *begin_of_comparison, t_list *current)
{
	void	*tmp;

	tmp = current->content;
	current->content = begin_of_comparison->content;
	begin_of_comparison->content = tmp;
}
