#include <stdbool.h>
#include "minishell.h"

char	*replace_key(t_dict_entry *expanded_var, char *result)
{
	if (expanded_var == NULL)
		result = append_str(result, "", 0);
	else
		result = append_str(\
		result, expanded_var->value, ft_strlen(expanded_var->value));
	return (result);
}

int	zero_init_vars(char **result, int *start, int *current, char *mode)
{
	*start = 0;
	*current = 0;
	*mode = 0;
	*result = ft_strdup("");
	if (*result == NULL)
		return (1);
	return (0);
}

bool is_not_in_heredoc(char *in, int current)
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
	char			*res;
	int				start;
	int				current;
	char			mode;

	if (in == NULL || zero_init_vars(&res, &start, &current, &mode))
		return (NULL);
	while ((current > 0 && in[current - 1]) \
			|| (current < (int) ft_strlen(in) && in[current]))
	{
		mode = update_mode((char *)&in[current], mode);
		if (in[current] == '$' || in[current] == 0)
		{
			res = append_str(res, &in[start], current - start);
			start = current;
			if (calc_key_len(&in[current]) != 0 && mode != SINGLE_QUOTE && is_not_in_heredoc(in, current))
			{
				res = replace_key(get_value_by_key(env, &in[current + 1]), res);
				current += calc_key_len(&in[current]);
				start = current + 1;
			}
		}
		current++;
	}
	return (res);
}

char	*expand_all_variables(t_list *env, char *in)
{
	char	*result;
	int		is_done;

	result = expand_one_layer_of_variables(env, in);
	is_done = ft_strncmp(in, result, calc_max_unsigned(\
			ft_strlen(in), ft_strlen(result))) == 0;
	if (is_done)
		return (result);
	return (expand_all_variables(env, result));
}