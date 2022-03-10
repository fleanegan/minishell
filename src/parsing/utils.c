#include "minishell.h"

void skip_whitespace(const char *input, int *start, int *current)
{
	if (*current)
		*start = *current;
	while (input[(*start)] && ft_isspace(input[(*start)]))
		(*start)++;
	(*current) = (*start);
}

char	*strdup_from_to(const char *str, int start, int end)
{
	char 	*res;
	int		i;

	if (str == NULL || start > end)
		return (NULL);
	res = malloc((end - start + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		res[i] = str[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

t_cmd *new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->exec_name = NULL;
	cmd->args = NULL;
	cmd->redir_file_name = NULL;
	cmd->token = EMPTY;
	return (cmd);
}

static char update_mode_for_type(char *input, char mode, char quote_type)
{
	if (mode == 0 && *input == quote_type && ft_strchr(input + 1, quote_type))
	{
		if (quote_type == SINGLE_QUOTE)
			return (SINGLE_QUOTE);
		else
			return (DOUBLE_QUOTE);
	}
	else if (*input == mode)
		return (NOT_IN_QUOTE);
	return (mode);
}

char update_mode(char *input, char mode)
{
	char res = update_mode_for_type(input, mode, SINGLE_QUOTE);
	if (res)
	{
		return res;
	}
	return (update_mode_for_type(input, mode, DOUBLE_QUOTE));
}