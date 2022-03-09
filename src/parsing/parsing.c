#include "minishell.h"

int is_end_of_arg(int c)
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

//char update_mode(char input, char mode)
//{
//	if (mode == 0 && input == '\'')
//		return (1);
//	else if (mode == 1 && input == '\'')
//		return (0);
//	return (mode);
//}

char	*trim_result(char *result)
{
	char	*tmp;

	tmp = result;
	result = ft_strtrim(result, " \n\t");
	delete_quotes(result);
	free(tmp);
	return (result);
}

// protect malloc!
char *parse_until(const char *input, int *start, int *current, int(*stop_condition)(int))
{
	char	*result;
	char	mode;

	mode = 0;
	skip_whitespace(input, start, current);
	while (input[(*current)])
	{
		mode = update_mode((char *)&input[*current], mode);
		if (mode == NOT_IN_QUOTE && stop_condition(input[(*current)]))
			break ;
		// expand env vars here
		(*current)++;
	}
	result = strdup_from_to(input, (*start), (*current) - 1);
	return (trim_result(result));
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
                    parse_until(input, &start, &current, ft_isspace);
		get_content(current_cmd)->args = parse_until(input, &start, &current, is_end_of_arg);
		parse_token(input, &start, &current);
	}
	return (result_cmd);
}
//		printf("len: %lu, start: %d, current: %d, current char: %d\n", strlen(input), start, current, input[current-1]);


