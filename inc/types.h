/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:09:43 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:09:45 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# define SPACE_FOR_NULLTERMIN 1
# define SPACE_FOR_EXEC_NAME 1
# define DOUBLE_QUOTE '\"'
# define NOT_IN_QUOTE 0
# define SINGLE_QUOTE '\''
# define NB_BUILT_INS 7
# define NO_ERR_BUT_QUIT (-2)

extern int	g_is_ctrl_c;

typedef enum e_token
{
	EMPTY = 0,
	PIPE,
	REDIR_OUT_REPLACE,
	REDIR_OUT_APPEND,
	REDIR_IN_FILE,
	REDIR_IN_HERE_DOC
}		t_token;

typedef enum e_env_mode
{
	ENV_REPLACE_VAR,
	ENV_APPEND_VAR
}	t_env_mode;

typedef struct s_string_slice
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
	t_token	outtoken;
	t_token	pipe;
}			t_cmd;

typedef struct s_built_in_entry
{
	char	*name;
	int		(*func_ptr)(t_list **env, t_list **cmd, int index);
}	t_built_in_entry;

typedef enum e_print_env_mode
{
	PRINT_ENV,
	PRINT_EXPORT
}	t_print_env_mode;
#endif //TYPES_H
