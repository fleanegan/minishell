/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:16:22 by                   #+#    #+#             */
/*   Updated: 2021/12/13 11:33:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	save_fd_rest(t_list_sav **sav, int fd, char *content)
{
	t_list_sav	*tmp;
	t_list_sav	*new;

	new = malloc(sizeof(t_list_sav));
	if (new)
	{
		new->fd = fd;
		new->content = content;
		new->next = NULL;
	}
	else
		return ;
	if (! *sav)
		*sav = new;
	else
	{
		tmp = *sav;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*pop_fd_res(t_list_sav **sav, int fd)
{
	t_list_sav	*tmp;
	t_list_sav	*last;
	char		*res;

	if (!sav)
		return (NULL);
	tmp = *sav;
	last = NULL;
	res = NULL;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			if (! last)
				*sav = tmp->next;
			else
				last->next = tmp->next;
			res = tmp->content;
			free(tmp);
			break ;
		}
		last = tmp;
		tmp = tmp->next;
	}
	return (res);
}

int	calc_pos_of_char_n(const char *buf, char n, int max_len)
{
	int	index;

	index = 0;
	if (! buf)
		return (HAS_NOT_BEEN_FOUND);
	while (buf[index] || ! n)
	{
		if (max_len >= 0 && index >= max_len)
			break ;
		if (buf[index] == n)
			return (index);
		else
			index++;
	}
	return (HAS_NOT_BEEN_FOUND);
}

char	*concat_n_char_new_mem(char *first, const char *buf,
			int chars_to_append)
{
	char	*tmp;
	int		size_alloc;
	int		end_of_first_string;
	int		ctr;

	ctr = -1;
	if (! buf)
		return (NULL);
	size_alloc = chars_to_append + SPACE_FOR_NULLTERMIN;
	tmp = malloc(sizeof(char) * size_alloc);
	if (!tmp)
		return (NULL);
	end_of_first_string = calc_pos_of_char_n(first, 0, -1);
	if (end_of_first_string == HAS_NOT_BEEN_FOUND)
		end_of_first_string = 0;
	tmp[--size_alloc] = NULLTERMIN;
	while (++ctr < size_alloc)
	{
		if (ctr < end_of_first_string)
			tmp[ctr] = first[ctr];
		else
			if (ctr - end_of_first_string < chars_to_append)
				tmp[ctr] = buf[ctr - end_of_first_string];
	}
	return (tmp);
}

void	free_linked_list(t_list_sav **pSav)
{
	t_list_sav	*temp;
	t_list_sav	*next;

	if (! pSav)
		return ;
	temp = *pSav;
	while (temp)
	{
		next = temp->next;
		if (temp->content)
			free(temp->content);
		free(temp);
		temp = next;
	}
	*pSav = NULL;
}
