#include "minishell.h"


int parse_next_field(t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *sub);
int append_next_argument_to_list(t_list **arg_tmp, t_string_slice *sub, t_list **tmp_arg);

int cpy_str(void *content, void **result)
{
	(*result) = ft_strdup((char *)content);
	if (*result == NULL)
		return (1);
	return (0);
}

t_list	*flexparse(char *input, t_list *env)
{
	t_list  		*result_cmd;
	t_list  		*current_cmd;
	t_list			*arg_tmp;
	t_string_slice	current_substr;

	ft_bzero(&current_substr, sizeof(current_substr));
	current_substr.src = input;
	result_cmd = NULL;
	arg_tmp = NULL;
	move_start_and_end_behind_whitespace(&current_substr);
	while (current_substr.src[current_substr.current])
	{
		append_new_cmd(&result_cmd, &current_cmd);
		while (get_content(current_cmd)->exec_name == NULL)
		{
			/* error is in first condition */
			if (parse_next_field(env, current_cmd, &arg_tmp, &current_substr) \
				|| get_content(current_cmd)->exec_name == NULL \
				|| (current_substr.src[current_substr.start] == '|' \
						&& parse_pipe(&current_substr, current_cmd)))
			{
				puts("clearing list");
				ft_lstclear(&result_cmd, free_cmd);
				ft_lstclear(&arg_tmp, free);
				free(input);
				return (NULL);
			}
			get_content(current_cmd)->args = (char **) to_array(arg_tmp, cpy_str);
			ft_lstclear(&arg_tmp, free);
		}
	}
	free(input);
	return (result_cmd);
}

int	parse_next_field(t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *sub)
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
