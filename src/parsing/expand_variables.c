#include "minishell.h"

void	copy_regular_text(char *in, t_string_slice *res);
void	expand_one_variable_if_possible(\
		t_list *env, char *in, t_string_slice *res, char mode);

int	is_not_in_heredoc(char *in, int current)
{
	while (current > 0)
	{
		if (is_token(in[current]))
		{
			if (in[current] == '<' && in[current - 1] == '<')
				return (0);
			else
				return (1);
		}
		current--;
	}
	return (1);
}

char	*expand_one_layer_of_variables(t_list *env, char *in)
{
	t_string_slice	res;
	char			mode;

	mode = 0;
	res.start = 0;
	res.current = 0;
	res.src = ft_strdup("");
	if (in == NULL || res.src == NULL)
	{
		free(res.src);
		return (NULL);
	}
	while (res.src != NULL && ((res.current > 0 && in[res.current - 1]) \
			|| (res.current < (int) ft_strlen(in) && in[res.current])))
	{
		mode = update_mode(&in[res.current], mode);
		if (in[res.current] == '$' || in[res.current] == 0)
		{
			copy_regular_text(in, &res);
			expand_one_variable_if_possible(env, in, &res, mode);
		}
		res.current++;
	}
	return (res.src);
}

void	expand_one_variable_if_possible(\
		t_list *env, char *in, t_string_slice *res, char mode)
{
	t_dict_entry	*variable;

	if (in[res->current] == 0 || in[res->current + 1] == 0)
		return ;
	res->current++;
	if (calc_key_len(&in[res->current]) != 0 \
		&& mode != SINGLE_QUOTE && is_not_in_heredoc(in, res->current))
	{
		variable = get_entry_by_key(env, &in[res->current]);
		if (variable == NULL)
			res->src = append_str(res->src, "", 0);
		else
			res->src = append_str(\
		res->src, variable->value, ft_strlen(variable->value));
		res->current += calc_key_len(&in[res->current]);
		res->start = res->current;
	}
	res->current--;
}

void	copy_regular_text(char *in, t_string_slice *res)
{
	res->src = append_str(\
	res->src, &in[res->start], res->current - res->start);
	res->start = res->current;
}

char	*expand_all_variables(t_list *env, char *in)
{
	char	*result;
	int		is_done;

	result = expand_one_layer_of_variables(env, in);
	is_done = ft_strncmp(in, result, calc_max_unsigned(\
			ft_strlen(in), ft_strlen(result))) == 0;
	free(in);
	if (is_done)
		return (result);
	return (expand_all_variables(env, result));
}
