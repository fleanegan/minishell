#include "minishell.h"


void parse_next_field(t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *current_substr);

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
	while (current_substr.src[current_substr.current])
	{
		append_new_cmd(&result_cmd, &current_cmd);
		while (get_content(current_cmd)->exec_name == NULL)
		{
			parse_next_field(env, current_cmd, &arg_tmp, &current_substr);
			if (get_content(current_cmd)->exec_name == NULL) {
				puts("clearing list");
				ft_lstclear(&result_cmd, free_cmd);
				ft_lstclear(&arg_tmp, free);
				free(input);
				return (NULL);
			}
			if (current_substr.src[current_substr.start] == '|' && parse_token(&current_substr, current_cmd, env))
				return (NULL);
			get_content(current_cmd)->args = (char **) to_array(arg_tmp, cpy_str);
			ft_lstclear(&arg_tmp, free);
		}
	}
	free(input);
	return (result_cmd);
	(void) env;
}

void	parse_next_field(t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *current_substr)
{
	while ((*current_substr).src[(*current_substr).current] && (*current_substr).src[(*current_substr).current] != '|')
	{
		if (is_token((*current_substr).src[(*current_substr).current])) {
			if ((*current_substr).src[(*current_substr).current] == '>' &&
				parse_redir_out(current_substr, current_cmd, env)) { puts("error"); }
			if ((*current_substr).src[(*current_substr).current] == '<' &&
				parse_redir_in(current_substr, current_cmd, env)) { puts("eroor"); }
		}
		//printf("parse name start: %d, current %d, string: %s\n", current_substr.start, current_substr.current, current_substr.src);
		if ((*current_substr).src[(*current_substr).current])
		{
			if (get_content(current_cmd)->exec_name == NULL)
			{
				if (parse_exec_name(current_substr, current_cmd))
					puts("eror");
			}
			else
				ft_lstadd_back(arg_tmp, ft_lstnew(parse_until(current_substr, ft_isspace)));
		}
	}
}

t_list *parsing(char *input, t_list *env)
{
	t_list  		*result_cmd;
	t_list  		*current_cmd;
	t_string_slice	current_substr;

	ft_bzero(&current_substr, sizeof(current_substr));
	current_substr.src = input;
	result_cmd = NULL;
	while (current_substr.src[current_substr.start])
	{
		if (append_new_cmd(&result_cmd, &current_cmd) \
 			|| parse_exec_name(&current_substr, current_cmd) \
 			|| parse_args(&current_substr, current_cmd) \
 			|| parse_token(&current_substr, current_cmd, env))
		{
			puts("clearing list");
			ft_lstclear(&result_cmd, free_cmd);
			free(input);
			return (NULL);
		}
	}
	free(input);
	return (result_cmd);
}
