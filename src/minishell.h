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

typedef enum	e_token
{
	EMPTY = 0
}		t_token;

typedef struct s_cmd
{
	char	*exec_name;
	char	*args;
	char	*redir_file_name;
	t_token	token;
}			t_cmd;

/*	Parsing	*/

t_list	*parsing(const char *input);

/*	Utils	*/

t_cmd	*get_content(t_list *in);
char	*strdup_from_to(const char *str, int start, int end);

/*	Tears_down	*/

void	free_cmd(void *cmd);

#endif //MINISHELL_H
