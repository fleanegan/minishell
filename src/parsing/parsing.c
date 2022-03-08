#include "minishell.h"

int is_end_of_arg(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

// protect malloc!
int	append_new_cmd(t_list **result_cmd, t_list **current_cmd)
{
	ft_lstadd_back(result_cmd, ft_lstnew(new_cmd()));
	*current_cmd = ft_lstlast((*result_cmd));
	if (*current_cmd == NULL || (*current_cmd)->content == NULL)
	{
		ft_lstclear(result_cmd, &free_cmd);
		return (1);
	}
	return (0);
}

// protect malloc!
char	*parse_exec_name(const char *input, int *start, int *current)
{
	skip_whitespace(input, start, current);
	while (input[(*current)] && !ft_isspace(input[(*current)]))
		(*current)++;
	return (strdup_from_to(input, (*start),(*current) - 1));
}

// protect malloc!
char *parse_args(const char *input, int *start, int *current)
{
	skip_whitespace(input, start, current);
	while (input[(*current)] && ! is_end_of_arg(input[(*current)]))
		(*current)++;
	return strdup_from_to(input, (*start), (*current) - 1);
}

t_token parse_token(const char *input, int *start, int *current)
{
	skip_whitespace(input, start, current);
	if (is_end_of_arg(input[(*start)]))
	{
		(*start)++;
		(*current)++;
	}
	return (0);
}

t_list *parsing(const char *input)
{
	t_list	*result_cmd;
	t_list	*current_cmd;
	int	start;
	int	current;

	current = 0;
	start = 0;
	result_cmd = NULL;
	while (input[start])
	{
		append_new_cmd(&result_cmd, &current_cmd);
		get_content(current_cmd)->exec_name = \
					parse_exec_name(input, &start, &current);
		get_content(current_cmd)->args = parse_args(input, &start, &current);
		parse_token(input, &start, &current);
	}
	return (result_cmd);
}

//		printf("len: %lu, start: %d, current: %d, current char: %d\n", strlen(input), start, current, input[current-1]);

