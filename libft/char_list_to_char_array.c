/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_to_char_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:29 by                   #+#    #+#             */
/*   Updated: 2022/02/05 13:16:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	**init_to_array(t_list *pList, void ***result, int *size, int *i);
static		void	remove_entry_if_cpy_is_null_but_no_error(\
			void *const *result, int *size, int *i);

char	*char_list_to_char_array(t_list *lst)
{
	char	*result;
	int		ctr;

	if (! lst)
		return (NULL);
	result = malloc((SPACE_FOR_NULLTERMIN + ft_lstsize(lst)) * sizeof(char));
	if (! result)
		return (NULL);
	ctr = 0;
	while (lst)
	{
		if (! *(char *)lst->content)
			break ;
		result[ctr] = *(char *)lst->content;
		ctr++;
		lst = lst->next;
	}
	result [ctr] = 0;
	return (result);
}

void	**to_array(t_list *pList, int (*cpy)(void *, void **))
{
	void	**result;
	int		size;
	int		i;

	if (init_to_array(pList, &result, &size, &i) == NULL)
		return (NULL);
	while (i < size)
	{
		if (pList->content == NULL)
		{
			pList = pList->next;
			size--;
			continue ;
		}
		if (cpy(pList->content, &result[i]))
		{
			free_2d_array(result);
			return (NULL);
		}
		remove_entry_if_cpy_is_null_but_no_error(result, &size, &i);
		i++;
		pList = pList->next;
	}
	return (result);
}

void	remove_entry_if_cpy_is_null_but_no_error(\
		void *const *result, int *size, int *i)
{
	if (result[(*i)] == NULL)
	{
		(*i)--;
		(*size)--;
	}
}

void	**init_to_array(t_list *pList, void ***result, int *size, int *i)
{
	*i = 0;
	if (pList == NULL)
		return ((void **) 1);
	*size = ft_lstsize(pList);
	*result = malloc(sizeof(t_list) * (*size + 1));
	if (*result == NULL)
		return (NULL);
	(*result)[*size] = NULL;
	return ((void **) 1);
}
