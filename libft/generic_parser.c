/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:26 by                   #+#    #+#             */
/*   Updated: 2022/02/05 11:34:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_file_valid(int fd);
void	*clean_up(void (*struct_destructor)(void *), \
		void *container, void *line);

void	*parse_file(char *file_name, void *(*struct_initializer)(const char *), \
		int (*struct_populator)(const char *, void *, int), \
		void (*struct_destructor)(void *))
{
	void	*container;
	int		fd;
	int		line_no;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (! is_file_valid(fd))
		return (NULL);
	container = struct_initializer(file_name);
	line_no = 0;
	while (container && gnl(fd, &line))
	{
		if (struct_populator(line, container, line_no))
			return (clean_up(struct_destructor, container, line));
		free(line);
		line_no++;
	}
	close(fd);
	return (container);
}

int	is_file_valid(int fd)
{
	if (fd < 2)
	{
		if (fd >= 0)
			close(fd);
		return (0);
	}
	return (1);
}

void	*clean_up(\
		void (*struct_destructor)(void *), void *container, void *line)
{
	free(line);
	gnl(-1, NULL);
	struct_destructor(container);
	return (NULL);
}

int	generic_split_line_parser(char *str, void *container, int line_no, \
	int (*struct_populate_grid_wise) \
	(const char *, void *, int, int))
{
	char	**columns;
	int		column_no;

	columns = ft_split(str, ' ');
	if (! columns)
		return (1);
	column_no = 0;
	while (columns[column_no])
	{
		if (struct_populate_grid_wise(columns[column_no], \
			container, line_no, column_no))
		{
			free_2d_array((void **) columns);
			return (1);
		}
		column_no++;
	}
	free_2d_array((void **) columns);
	return (0);
}
