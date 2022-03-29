#ifndef MINISHELL_H
# define MINISHELL_H
# include "unistd.h"
# include "unistd.h"
# include "stdlib.h"
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
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
# define NB_BUILT_INS 6

typedef enum	e_token
{
	EMPTY = 0,
	PIPE,
	REDIR_OUT_REPLACE,
	REDIR_OUT_APPEND,
	REDIR_IN_FILE,
	REDIR_IN_HERE_DOC
}		t_token;

typedef	enum	e_env_mode
{
	ENV_REPLACE_VAR,
	ENV_APPEND_VAR
}	t_env_mode;

typedef struct	s_string_slice
{
	char		*src;
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
	t_token	pipe;
}			t_cmd;

typedef	struct	s_built_in_entry
{
	char	*name;
	int		(*func_ptr)(t_list **env , t_cmd *cmd);
}	t_built_in_entry;

/* Init */
t_list *init(char **envp);
char			*expand_one_layer_of_variables(t_list *env, char *in);
char			*expand_all_variables(t_list *env, char *in);
int update_env(t_list **env, char *key, char *val, t_env_mode update_mode);

/*	Parsing	*/
t_list			*parse(char *input, t_list *env);
int				parse_args(t_string_slice *sub, t_list *current_cmd);
char			*delete_quotes(char *in);
char			update_mode(const char *input, char mode);
int     		append_new_cmd(t_list **result_cmd, t_list **current_cmd);
int				append_new_arg(t_list **tmp_args, char	*arg_str);
char    		*trim_result(char *result);
int				is_token(int c);
char			*fetch_heredoc_input(\
				t_list *env, const char *string, char *(*line_reader)(const char *));
char			*generate_heredoc(\
				t_list *env, const char *delimiter, char *(line_reader)(
				const char *));
char			*parse_until(t_string_slice *sub, int(*stop_condition)(int));
int				parse_redir_out(t_string_slice *sub, t_list *current_cmd);
int				parse_redir_in(t_string_slice *sub, t_list *current_cmd, t_list *env);
int				parse_pipe(t_string_slice *sub, t_list *current_cmd);
int				parse_redirection(t_list *env, t_list *current_cmd, t_string_slice *sub);
t_token			determine_redirection_type(t_string_slice *sub, t_list *current_cmd);
int				move_cursor_behind_token(t_string_slice *sub);
int				parse_next_attribute(t_list *env, t_list *current_cmd, \
				t_list **arg_tmp, t_string_slice *sub);
int				parse_one_command(t_string_slice *sub, t_list **result_cmd, t_list *env);
int				parse_exec_name(t_list *env, t_list *current_cmd, \
				t_list **arg_tmp,	t_string_slice *sub);
char			*get_path(char *exec_name, char *path);


/* Signal handling */
void			handle_ctrl_c(int signal_no, siginfo_t *info, void *hmm);
int				set_signal_handler(int signal_no, \
void 			(*handler_function)(int, siginfo_t *, void *));
void			handle_ctrl_c_heredoc(\
				int signal_no, siginfo_t *info, void *hmm);
void			handle_ctrl_c_parent(int signal_no, siginfo_t *info, void *hmm);
int set_sa_handler(int signal_no, __sighandler_t test);

/*	Execution	*/
int execution(t_list *cmd, t_list *env, int nb_cmd);
int				**ft_tabnew_two(int col, int line);
int 			ft_close(int *fd);
int close_before_exit_process(int **fd);
int exec_cmd(t_list *cmd, int i, int **fd, t_list *env);
int tear_down_parent(int nb_processes, int **fd, int pid_of_last_cmd);
int 			redirect_stdout_to_outfile(char *outfile, t_token mode);
void			init_pipes(int nb_processes, int **fd);
int				redirect_infile_to_stdin(char *infile);
int				redirect_stdout_into_pipe(int *fd_of_pipe);
int				redirect_stdin_into_pipe(int *fd_of_pipe);
void			init_pipes(int nb_processes, int **fd);
void			*get_built_in_function_pointer(const t_cmd *content);
int execute_built_in_parent(t_list *cmd, t_list *env, int i, int **fd);
int execute_cmd_in_fork(t_list *cmd, t_list *env, int i, int **fd);
int execute_execve(t_cmd *content, t_list *env);


/*	Utils		*/
t_cmd			*get_content(t_list *in);
void			move_cursor_behind_whitespace(t_string_slice *sub);
t_cmd			*new_cmd(void);
char			*append_str(char *base, char *appendix, int appendix_size);
int				calc_key_len(char *key);
t_dict_entry	*get_value_by_key(t_list *lst, char *key);
char			*read_file(char *name);
int				msh_strcmp(char *s1, char *s2);
char			char_under_cursor(t_string_slice in);
int				cpy_str(void *content, void **result);
int				cpy_dict_to_str(void *content, void **result);
void			*free_list_and_return_null(t_list **lst, void (*del)(void *));
int				parse_one_argument(\
				t_list **arg_tmp, t_string_slice *sub, t_list **current_arg);
t_string_slice	init_slice_at_start_of(char *input);

/*	Tear_down	*/
void			free_cmd(void *cmd);
void			free_dict_entry(void *dict_entry);
int tear_down_one_command(t_list **arg_tmp);

/* Built ins */
int				msh_env(t_list **env, t_cmd *cmd);
int				msh_unset(t_list **env, t_cmd *cmd);
int				msh_cd(t_list **env, t_cmd *cmd);
int				msh_export(t_list **env, t_cmd *cmd);
int				msh_pwd(t_list **env, t_cmd *cmd);
int				msh_echo(t_list **env, t_cmd *cmd);
int				print_all_env_vars_with_prefix(t_list **env, char *prefix);
// utils debug
void			print_cmd(t_list	*cmd);

#endif //MINISHELL_H
