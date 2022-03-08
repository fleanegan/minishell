#ifndef MINISHELL_H
# define MINISHELL_H
# include "unistd.h"
# include "unistd.h"
# include "stdlib.h"
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define SPACE_NULLTERMIN 1

typedef struct s_cmd
{
	char	*exec_name;
	char	*args;
	char	*redir_file_name;
	char	token;
}			t_cmd;

t_cmd	*parsing(const char *input);

#endif //MINISHELL_H
