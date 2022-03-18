#include "../minishell.h"

int parse_pipe(t_string_slice *sub, t_list *current_cmd)
{
	if (get_content(current_cmd)->outtoken)
		return (1);
	get_content(current_cmd)->outtoken = PIPE;
	while (1)
	{
		if (! is_token(sub->src[sub->start]) && ! ft_isspace(sub->src[sub->start]))
			return (0);
		(sub->start)++;
		(sub->current)++;
		if (! sub->src[sub->start] || is_token(sub->src[sub->start]))
			return (1);
	}
	move_start_and_end_behind_whitespace(sub);
}

int parse_redir_out(t_string_slice *sub, t_list *current_cmd, t_list *env)
{
	get_content(current_cmd)->outtoken = REDIR_OUT_REPLACE;
	if (sub->src[sub->start + 1] == sub->src[sub->start])
	{
		(sub->start)++;
		(sub->current)++;
		get_content(current_cmd)->outtoken = REDIR_OUT_APPEND;
	}
	(sub->start)++;
	(sub->current)++;
	if (! sub->src[sub->current] || is_token(sub->src[sub->current]))
		return (1);
	free(get_content(current_cmd)->outfile);
	get_content(current_cmd)->outfile = parse_until(sub, ft_isspace);
	if (get_content(current_cmd)->outfile == NULL)
		return (1);
	delete_quotes(get_content(current_cmd)->outfile);
	move_start_and_end_behind_whitespace(sub);
	return (parse_token(sub, current_cmd, env));
}

int parse_redir_in(t_string_slice *sub, t_list *current_cmd, t_list *env)
{
	char	*parsed_infile;
	get_content(current_cmd)->intoken = REDIR_IN_FILE;
	if (sub->src[sub->start + 1] == sub->src[sub->start])
	{
		(sub->start)++;
		(sub->current)++;
		get_content(current_cmd)->intoken = REDIR_IN_HERE_DOC;
	}
	move_start_and_end_behind_whitespace(sub);
	if (! sub->src[sub->current] || ! sub->src[sub->current + SPACE_FOR_NULLTERMIN])
		return (1);
	(sub->start)++;
	(sub->current)++;
	free(get_content(current_cmd)->infile);
	parsed_infile = parse_until(sub, ft_isspace);
	get_content(current_cmd)->infile = parsed_infile;
	if (get_content(current_cmd)->intoken == REDIR_IN_HERE_DOC)
	{
		show_list(env);
		get_content(current_cmd)->infile = \
		generate_heredoc(env, parsed_infile,readline);
		free(parsed_infile);
	}
	move_start_and_end_behind_whitespace(sub);
	return (parse_token(sub, current_cmd, env));
}
