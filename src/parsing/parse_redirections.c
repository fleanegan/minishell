#include "../minishell.h"

int parse_pipe(const char *in, int *start, int *current, t_list *current_cmd)
{
	if (get_content(current_cmd)->outtoken)
		return (1);
	get_content(current_cmd)->outtoken = PIPE;
	while (1)
	{
		if (! is_token(in[*start]) && ! ft_isspace(in[*start]))
			return (0);
		(*start)++;
		(*current)++;
		if (! in[*start] || is_token(in[*start]))
			return (1);
	}
}

int	parse_redir_out(const char *in, int *start, int *current, t_list *current_cmd)
{
	get_content(current_cmd)->outtoken = REDIR_OUT_REPLACE;
	if (in[*start + 1] == in[*start])
	{
		(*start)++;
		(*current)++;
		get_content(current_cmd)->outtoken = REDIR_OUT_APPEND;
	}
	move_start_and_end_behind_whitespace(in, start, current);
	(*start)++;
	(*current)++;
	if (! in[*current] || is_token(in[*current]))
		return (1);
	free(get_content(current_cmd)->outfile);
	get_content(current_cmd)->outfile = parse_until(in, start, current, ft_isspace);
	if (get_content(current_cmd)->outfile == NULL)
		return (1);
	delete_quotes(get_content(current_cmd)->outfile);
	return (parse_token(in, start, current, current_cmd));
}

int	parse_redir_in(const char *in, int *start, int *current, t_list *current_cmd)
{
	get_content(current_cmd)->intoken = REDIR_IN_FILE;
	move_start_and_end_behind_whitespace(in, start, current);
	if (! in[*current] || ! in[*current + SPACE_FOR_NULLTERMIN])
		return (1);
	(*start)++;
	(*current)++;
	free(get_content(current_cmd)->infile);
	get_content(current_cmd)->infile =  parse_until(in, start, current, ft_isspace);
	return (parse_token(in, start, current, current_cmd));
}
