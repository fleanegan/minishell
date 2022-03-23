#include "minishell.h"

int	zero_init_vars(t_string_slice *res, char *mode)
{
	res->start = 0;
	res->current = 0;
	*mode = 0;
	res->src = ft_strdup("");
	if (res->src == NULL)
		return (1);
	return (0);
}

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

int	expand_variable_under_cursor(t_list *env, char *in, t_string_slice *res)
{
	t_dict_entry	*variable;

	variable = get_value_by_key(env, &in[res->current + 1]);
	if (variable == NULL)
		res->src = append_str(res->src, "", 0);
	else
		res->src = append_str(\
		res->src, variable->value, ft_strlen(variable->value));
	if (res->src == NULL)
		return (1);
	res->current += calc_key_len(&in[res->current]);
	res->start = res->current + 1;
	return (0);
}

char	*expand_one_layer_of_variables(t_list *env, char *in)
{
	t_string_slice	res;
	char			mode;

	if (in == NULL || zero_init_vars(&res, &mode))
		return (NULL);
	while ((res.current > 0 && in[res.current - 1]) \
			|| (res.current < (int) ft_strlen(in) && in[res.current]))
	{
		mode = update_mode(&in[res.current], mode);
		if (in[res.current] == '$' || in[res.current] == 0)
		{
			res.src = append_str(\
			res.src, &in[res.start], res.current - res.start);
			res.start = res.current;
			if (calc_key_len(&in[res.current]) != 0 \
			&& mode != SINGLE_QUOTE && is_not_in_heredoc(in, res.current))
				if (expand_variable_under_cursor(env, in, &res))
					return (NULL);
		}
		res.current++;
	}
	return (res.src);
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
