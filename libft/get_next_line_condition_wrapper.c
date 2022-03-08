/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_condition_wrapper.h                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:17:26 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:12:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl(int fd, char **line)
{
	if (fd < 0 || BUFFER_SIZE < 0 || !line)
	{
		get_next_line(-1);
		return (-1);
	}
	*line = get_next_line(fd);
	if (*line)
		return (1);
	return (0);
}
