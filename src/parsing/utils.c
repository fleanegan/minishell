#include "minishell.h"

char	*strdup_from_to(t_string_slice sub)
{
	char	*res;
	int		i;

	if (sub.src == NULL || sub.start > sub.current - 1)
		return (NULL);
	res = malloc((\
			sub.current - sub.start + SPACE_FOR_NULLTERMIN) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (sub.start <= sub.current - 1)
	{
		res[i] = sub.src[sub.start];
		i++;
		sub.start++;
	}
	res[i] = '\0';
	return (res);
}

static char	update_mode_for_type(const char *input, char mode, char quote_type)
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

char	update_mode(const char *input, char mode)
{
	char	res;

	res = update_mode_for_type(input, mode, SINGLE_QUOTE);
	if (res)
	{
		return (res);
	}
	return (update_mode_for_type(input, mode, DOUBLE_QUOTE));
}

int	is_token(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

char	*trim_result(char *result)
{
	char	*tmp;

	if (result == NULL)
		return (NULL);
	tmp = result;
	result = ft_strtrim(result, " \n\t");
	free(tmp);
	return (result);
}

t_token	determine_redirection_type(t_string_slice *sub, t_list *current_cmd)
{
	t_token	result;

	if (sub->src[sub->current] == '>')
	{
		result = REDIR_OUT_REPLACE;
		if (sub->src[sub->start + 1] == sub->src[sub->start])
		{
			(sub->start)++;
			(sub->current)++;
			result = REDIR_OUT_APPEND;
		}
		get_content(current_cmd)->outtoken = result;
	}
	else if (sub->src[sub->start] == '<')
	{
		result = REDIR_IN_FILE;
		if (sub->src[sub->start + 1] == sub->src[sub->start])
		{
			(sub->start)++;
			(sub->current)++;
			result = REDIR_IN_HERE_DOC;
		}
		get_content(current_cmd)->intoken = result;
	}
	return (result);
}

char	*read_file(char *name)
{
	char	*result;
	char	*line;
	int		fd;

	fd = open(name, O_RDONLY);
	result = ft_strdup("");
	while (gnl(fd, &line) == 1)
	{
		result = append_str(result, line, (int)ft_strlen(line));
		free(line);
	}
	if (close(fd))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
