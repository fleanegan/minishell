#include "minishell.h"


int parse_next_attribute(t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *sub);
int append_next_argument_to_list(t_list **arg_tmp, t_string_slice *sub, t_list **tmp_arg);
int parse_one_command(char *input, t_list *env, t_list **result_cmd, t_string_slice *current_substr);

t_list	*parse(char *input, t_list *env)
{
	t_list  		*result_cmd;
	t_string_slice	current_substr;

	ft_bzero(&current_substr, sizeof(current_substr));
	current_substr.src = input;
	result_cmd = NULL;
	move_cursor_behind_whitespace(&current_substr);
	while (current_substr.src[current_substr.current] != 0)
	{
		if (parse_one_command(input, env, &result_cmd, &current_substr))
			return (free_list_and_return_null(&result_cmd, free_cmd));
	}
	if (result_cmd != NULL \
		&& get_content(ft_lstlast(result_cmd))->outtoken == PIPE)
		return (free_list_and_return_null(&result_cmd, free_cmd));
	free(input);
	return (result_cmd);
}

int parse_one_command(char *input, t_list *env, t_list **result_cmd, t_string_slice *current_substr) {
	t_list  		*current_cmd;
	t_list			*arg_tmp;

	arg_tmp = NULL;
	append_new_cmd(result_cmd, &current_cmd);
	append_new_arg(&arg_tmp, ft_strdup(""));
	while (get_content(current_cmd)->exec_name == NULL)
	{
		if (parse_next_attribute(env, current_cmd, &arg_tmp, current_substr) \
			 || get_content(current_cmd)->exec_name == NULL \
			 || (current_substr->src[current_substr->start] == '|' \
			 		&& parse_pipe(current_substr, current_cmd)))
		{
			puts("clearing list");
			ft_lstclear(result_cmd, free_cmd);
			ft_lstclear(&arg_tmp, free);
			free(input);
			return (1);
		}
		get_content(current_cmd)->args = (char **) to_array(arg_tmp, cpy_str);
		ft_lstclear(&arg_tmp, free);
	}
	return (0);
}

int	parse_next_attribute(t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *sub)
{
	t_list	*tmp_arg;

	while (char_under_cursor(*sub) != 0 && char_under_cursor(*sub) != '|')
	{
		if (is_token(char_under_cursor(*sub)) && \
			parse_redirection(env, current_cmd, sub))
				return (1);
		if (get_content(current_cmd)->exec_name == NULL)
		{
			if (parse_exec_name(sub, current_cmd))
				return (1);
		}
		// error is in here
		else if (is_token(char_under_cursor(*sub)) == 0 \
			&& append_next_argument_to_list(arg_tmp, sub, &tmp_arg))
				return (1);
	}
	return (0);
}

int clear_list_and_return_null(t_list **tmp_arg) {
	ft_lstclear(tmp_arg, free);
	return (1);
}
