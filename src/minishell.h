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
# include "../libft/libft_auxilliar.h"
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

typedef struct	s_string_slice
{
	const char	*src;
	int			start;
	int			current;

}	t_string_slice;

typedef struct s_dict_entry
{
	char	*key;
	char	*value;
}	t_dict_entry;

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
t_list			*init();
t_dict_entry	*get_value_by_key(t_list *lst, char *key);
char			*expand_one_layer_of_variables(t_list *env, char *in);
char			*expand_all_variables(t_list *env, char *in);
int				append_to_dict(t_list **dict, char *key, char *value);

/*	Parsing	*/
t_list 			*parsing(char *input, t_list *env);
int 			parse_token(t_string_slice *sub, t_list *current_cmd, t_list *env);
int				parse_args(t_string_slice *sub, t_list *current_cmd);
int				parse_exec_name(t_string_slice *sub, t_list *current_cmd);
char			*delete_quotes(char *in);
char			**split_args(char *in);
int				split_count_substrings(char *in);
char			*get_first_quote(char *in);
char			update_mode(const char *input, char mode);
int     		append_new_cmd(t_list **result_cmd, t_list **current_cmd);
char    		*trim_result(char *result);
int				is_token(int c);
char			*fetch_heredoc_input(\
				t_list *env, const char *string, char *(*line_reader)(
		const char *));
char			*generate_heredoc(\
				t_list *env, const char *delimiter, char *(line_reader)(
				const char *));
char			*parse_until(t_string_slice *sub, int(*stop_condition)(int));
int parse_redir_out(t_string_slice *sub, t_list *current_cmd, t_list *env);
int parse_redir_in(t_string_slice *sub, t_list *current_cmd, t_list *env);
int				parse_pipe(t_string_slice *sub, t_list *current_cmd);

/* Signal handling */
void			handle_ctrl_c(int signal_no, siginfo_t *info, void *hmm);
void			handle_ctrl_d(int signal_no, siginfo_t *info, void *hmm);
void			handle_ctrl_backslash(int signal_no, siginfo_t *info, void *hmm);
int				set_signal_handler(int signal_no, \
void 			(*handler_function)(int, siginfo_t *, void *));

/*	Execution	*/
void			execution(t_list *cmd, char *env);
char			*get_path(char *exec_name, char *path);

/*	Utils		*/
t_cmd			*get_content(t_list *in);
char			*strdup_from_to(t_string_slice sub);
void			move_start_and_end_behind_whitespace(t_string_slice *sub);
t_cmd			*new_cmd(void);
char			*append_str(char *base, char *appendix, int appendix_size);
int				calc_key_len(char *key);
char			*read_file(char *name);
void			show_list(t_list *lst);

/*	Tear_down	*/
void			free_cmd(void *cmd);
void			free_dict_entry(void *dict_entry);

#endif //MINISHELL_H
