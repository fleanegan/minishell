/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:17:26 by                   #+#    #+#             */
/*   Updated: 2021/12/13 16:32:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define SPACE_FOR_NULLTERMIN 1
# define SPACE_FOR_NEWLINE 1
# define NULLTERMIN 0
# define HAS_NOT_BEEN_FOUND -1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 150
# endif //BUFFER_SIZE
# ifdef own_source
#  define BUFFER_SIZE 2
# endif

# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list_sav
{
	char				*content;
	struct s_list_sav	*next;
	int					fd;
	int					len;
}	t_list_sav;

int		calc_pos_of_char_n(const char *buf, char n, int max_len);
char	*concat_n_char_new_mem(char *first, const char *buf,
			int chars_to_append);
char	*get_next_line(int fd);
void	save_fd_rest(t_list_sav **sav, int fd, char *content);
char	*pop_fd_res(t_list_sav **sav, int fd);
void	free_linked_list(t_list_sav **pSav);
int		gnl(int fd, char **line);

#endif