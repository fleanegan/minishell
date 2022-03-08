/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:00:26 by                   #+#    #+#             */
/*   Updated: 2022/02/05 11:34:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define SPACE_NULLTERMIN 1
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line_bonus.h"

// part 1
int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isspace(int input);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, \
				const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);

// part 2
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int tmp);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

// bonus part
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
				void (*del)(void *));
t_list			*ft_lstget_element_by_index(t_list *lst, size_t index);
t_list			*ft_lstget_element_by_function(t_list *pList, \
				int (*equals)(void *, int), int i);
int				ft_lstadd_element_at_index(t_list **lst, t_list *new, \
size_t index);
void			ft_lstsort(t_list **lst, int (*comp_func)(void *, void *));
int				ft_lstget_index_of_element(t_list *lst, t_list *element);
int				ft_lstcompare(t_list *a, t_list *b, \
				int (*compare)(void *, void *));
unsigned int	ft_abs(int in);
size_t			count_entries_in_2d_char_array(char **arr2d);
void			free_2d_array(void **mem);
char			*char_list_to_char_array(t_list *lst);
void			*parse_file(char *file_name, \
				void *(*struct_initializer)(const char *), \
				int (*struct_populator)(const char *, void *, int), \
				void (*struct_destructor)(void *));
int				generic_split_line_parser(char *str, void *container, \
				int line_no, \
				int (*struct_populate_grid_wise) \
				(const char *, void *, int, int));

#endif
