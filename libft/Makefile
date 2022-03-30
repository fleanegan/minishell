SRCS	= 	ft_substr.c \
			ft_putchar_fd.c \
			ft_strncmp.c \
			ft_strcmp.c \
			free_2d_array.c \
			ft_atoi.c \
			ft_split.c \
			ft_strchr.c \
			ft_putnbr_fd.c \
			ft_itoa.c \
			ft_memcmp.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strrchr.c \
			ft_memset.c \
			ft_strdup.c \
			ft_calloc.c \
			ft_toupper.c \
			ft_putendl_fd.c \
			ft_isdigit.c \
			calc_min.c \
			ft_strtrim.c \
			ft_strlen.c \
			ft_isprint.c \
			ft_memcpy.c \
			ft_strmapi.c \
			ft_tolower.c \
			ft_strnstr.c \
			ft_putstr_fd.c \
			ft_bzero.c \
			ft_striteri.c \
			ft_isupper.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_memchr.c \
			ft_islower.c \
			ft_memmove.c \
			ft_isspace.c \
			ft_strjoin.c \
			ft_isascii.c \
			ft_abs.c \
			ft_lstiter.c \
			ft_lstsize.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstnew.c \
			ft_lstsort.c \
			ft_lstlast.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstmap.c \
			ft_lstcompare.c \
			ft_lstrmnode.c \
			ft_lst_nullterminate.c \
			ft_lstput_nbr.c \
			ft_memccpy.c \
			is_charinset.c  \
			calc_digits_in_number.c \
			ft_lstget_element_by_index.c \
			ft_lstadd_element_at_index.c \
			ft_lstget_index_of_element.c \
			get_next_line_utils_bonus.c \
			get_next_line_bonus.c \
			get_next_line_condition_wrapper.c \
			count_entries_in_2d_char_array.c \
			char_list_to_char_array.c \
			malloc_int.c \
			generic_parser.c \

SRCSB	=   $(SRCS)

OBJS	= ${SRCS:.c=.o}

OBJSB	= ${SRCSB:.c=.o}

NAME	= libft.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS} $(SRCS)
		ar rc ${NAME} ${OBJS}

all:	${NAME}

bonus:	${OBJSB} $(SRCSB)
		ar rc ${NAME} ${OBJSB}

clean:
		${RM} ${OBJSB}

fclean:	clean
		${RM} ${NAME}

re:		fclean all


