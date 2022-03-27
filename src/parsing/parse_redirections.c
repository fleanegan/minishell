#include "../minishell.h"

int	parse_pipe(t_string_slice *sub, t_list *current_cmd)
{
	get_content(current_cmd)->pipe = PIPE;
	while (1)
	{
		if (! is_token(sub->src[sub->start]) \
			&& ! ft_isspace(sub->src[sub->start]))
			return (0);
		(sub->start)++;
		(sub->current)++;
	}
}

int	parse_redirection(t_list *env, t_list *current_cmd, t_string_slice *sub)
{
	t_token	type;

	type = determine_redirection_type(sub, current_cmd);
	if (move_cursor_behind_token(sub))
		return (1);
	if ((type == REDIR_OUT_APPEND || type == REDIR_OUT_REPLACE) \
		&& parse_redir_out(sub, current_cmd))
		return (1);
	if ((type == REDIR_IN_FILE || type == REDIR_IN_HERE_DOC) \
		&& parse_redir_in(sub, current_cmd, env))
		return (1);
	move_cursor_behind_whitespace(sub);
	return (0);
}

int	create_file_for_redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT, 0644);
	if (fd == -1 || ft_close(&fd) == 1)
		return (errno);
	return (0);
}

int	parse_redir_out(t_string_slice *sub, t_list *current_cmd)
{
	free(get_content(current_cmd)->outfile);
	(get_content(current_cmd))->outfile = parse_until(sub, ft_isspace);
	if (get_content(current_cmd)->outfile == NULL)
		return (1);
	if (create_file_for_redir_out((get_content(current_cmd))->outfile) != 0)
		return (1);
	return (0);
}

int	parse_redir_in(t_string_slice *sub, t_list *current_cmd, t_list *env)
{
	char	*parsed_infile;

	free(get_content(current_cmd)->infile);
	parsed_infile = parse_until(sub, ft_isspace);
	get_content(current_cmd)->infile = parsed_infile;
	if (get_content(current_cmd)->intoken == REDIR_IN_HERE_DOC)
	{
		// TODO: testme
		(get_content(current_cmd))->infile = \
		generate_heredoc(env, parsed_infile, readline);
		if ((get_content(current_cmd))->infile == NULL)
			return (1);
		free(parsed_infile);
	}
	return (0);
}
