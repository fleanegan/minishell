#ifndef MINISHELL_H
# define MINISHELL_H
# include "unistd.h"
# include "unistd.h"
# include "stdlib.h"
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"
# define SPACE_FOR_NULLTERMIN 1
# define SPACE_FOR_EXEC_NAME 1
# define DOUBLE_QUOTE '\"'
# define NOT_IN_QUOTE 0
# define SINGLE_QUOTE '\''

typedef enum	e_token
{
	EMPTY = 0,
	PIPE,
	REDIR_OUT_REPLACE,
	REDIR_OUT_APPEND,
	REDIR_IN_FILE,
	REDIR_IN_HERE_DOC
}		t_token;

typedef struct s_cmd
{
	char	*exec_name;
	char	**args;
	char	*infile;
	char	*outfile;
	t_token	intoken;
	t_token outtoken;
}			t_cmd;

/* Init */
int		init();

/*	Parsing	*/
t_list	*parsing(const char *input);
int		parse_token(const char *in, \
		int *start, int *current, t_list *current_cmd);
int		parse_args( \
		const char *input, t_list *current_cmd, int *start, int *current);
int		parse_exec_name(const char *input, \
		t_list *current_cmd, int *start, int *current);
char	*delete_quotes(char *in);
char	**split_args(char *in);
int		count_substrings(char *in);
char	*get_first_quote(char *in);
char	update_mode(char *input, char mode);
int     append_new_cmd(t_list **result_cmd, t_list **current_cmd);
char    *trim_result(char *result);
int		is_token(int c);

/* Signal hanling */
void	handle_ctrl_c(int signal_no, siginfo_t *info, void *hmm);
void	handle_ctrl_d(int signal_no, siginfo_t *info, void *hmm);
void	handle_ctrl_backslash(int signal_no, siginfo_t *info, void *hmm);
int		set_signal_handler(int signal_no, \
		void (*handler_function)(int, siginfo_t *, void *));

/*	Execution	*/
void	execution(char *path, char **args, char *env);

/*	Utils		*/
t_cmd	*get_content(t_list *in);
char	*strdup_from_to(const char *str, int start, int end);
void	move_start_and_end_behind_whitespace(const char *input, int *start, int *current);
t_cmd	*new_cmd(void);

/*	Tear_down	*/
void	free_cmd(void *cmd);

#endif //MINISHELL_H
