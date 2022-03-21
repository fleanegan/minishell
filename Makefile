NAME = minishell

# Paths
SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/

# Names
SRC_NAME =	main.c \
			init.c \
			utils.c \
			signals.c \
			tear_down.c \
			expand_variables.c \
			parsing/parse.c \
			parsing/parse_redirections.c \
			parsing/heredoc.c \
			parsing/init.c \
			parsing/string_splice_utils.c \
			parsing/utils.c \
			parsing/delete_quotes.c \
			execution/execution.c \

TEST_SRC_NAME = test_main.c \

TEST_HEADER_NAME =	test_utils.h \

OBJ_NAME = $(SRC_NAME:.c=.o)

# Files
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
TEST_SRC = $(addprefix $(TEST_PATH),$(TEST_SRC_NAME))
TEST_HEADER = $(addprefix $(TEST_PATH),$(TEST_HEADER_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
LIBS		= -lreadline -Llibft -lft -Ilibft
TEST_FLAGS	= -g3 -L./criterion-v2.3.3/lib -I./criterion-v2.3.3/include -lcriterion -Wl,-rpath=./criterion-v2.3.3/lib

ifeq ($(MAKECMDGOALS),test)
	CFLAGS += -D IS_TEST
endif
ifeq ($(MAKECMDGOALS),testinc)
	CFLAGS += -D IS_TEST
endif

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Build $(NAME)"
	@make -C libft/ --no-print-directory
	@echo CFLAGS=${CFLAGS}
	@$(CC) -g $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -g -I$(SRC_PATH) -o $@ -c $< $(LIBS)

clean:
	@rm -rf $(OBJ_PATH) db
	@make -C libft/ clean --no-print-directory

fclean:	clean
	@rm -f $(NAME) db
	@make -C libft/ fclean --no-print-directory


test: $(OBJ) $(SRC) $(TEST_SRC) $(TEST_HEADER)
	@make -C libft/ --no-print-directory
	@$(CC) $(CFLAGS) $(TEST_FLAGS) -o $(NAME)_test $(OBJ) -I./$(SRC_PATH) $(TEST_SRC) $(LIBS)

re:	fclean all

test_clean: fclean test

.PHONY: all clean fclean re mlx libft db test
