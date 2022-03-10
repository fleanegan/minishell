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
# define SPACE_FOR_NULLTERMIN 1
# define SPACE_FOR_EXEC_NAME 1
# define DOUBLE_QUOTE '\"'
# define NOT_IN_QUOTE 0
# define SINGLE_QUOTE '\''

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
char	*delete_quotes(char *in);
char	**split_args(char *in);
int		count_substrings(char *in);
char	*get_first_quote(char *in);
char	update_mode(char *input, char mode);


/*	Utils	*/

t_cmd	*get_content(t_list *in);
char	*strdup_from_to(const char *str, int start, int end);
void	skip_whitespace(const char *input, int *start, int *current);
t_cmd	*new_cmd(void);


/*	Tears_down	*/

void	free_cmd(void *cmd);

#endif //MINISHELL_H
