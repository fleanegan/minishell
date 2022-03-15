#include "minishell.h"

char	*append_str(char *base, char *appendix, int appendix_size)
{
	int		base_size;
	char	*result;

	if (base == NULL || appendix == NULL)
		return (NULL);
	base_size = ft_strlen(base);
	result = ft_calloc((base_size + appendix_size + SPACE_FOR_NULLTERMIN), \
		sizeof(char));
	if (result == NULL)
	{
		free(base);
		return (NULL);
	}
	ft_strlcpy(\
	result, base, base_size + SPACE_FOR_NULLTERMIN);
	ft_strlcat(\
	result, appendix, base_size + appendix_size + SPACE_FOR_NULLTERMIN);
	free(base);
	return (result);
}

char	*replace_key(t_dict_entry *expanded_var, char *result)
{
	if (expanded_var == NULL)
		result = append_str(result, "", 0);
	else
		result = append_str(\
		result, expanded_var->value, ft_strlen(expanded_var->value));
	return (result);
}

int	zero_init_vars(char **result, int *start, int *current)
{
	*start = 0;
	*current = 0;
	*result = ft_strdup("");
	if (*result == NULL)
		return (1);
	return (0);
}

char	*expand_variables(t_list *env, char *in)
{
	t_dict_entry	*expanded_var;
	char			*result;
	int				start;
	int				current;
	char			mode;

	mode = 0;
	if (in == NULL || zero_init_vars(&result, &start, &current))
		return (NULL);
	while (in[current] || in[current - 1])
	{
		mode = update_mode((char *)&in[current], mode);
		if (in[current] == '$' || in[current] == 0)
		{
			result = append_str(result, &in[start], current - start);
			start = current;
			if (calc_key_len(&in[current]) != 0 && mode != SINGLE_QUOTE)
			{
				expanded_var = get_value_by_key(env, &in[current]);
				current += calc_key_len(&in[current]);
				result = replace_key(expanded_var, result);
				start = current + 1;
			}
		}
		current++;
	}
	return (result);
}
