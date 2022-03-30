#include "minishell.h"

static int	is_invalid_input(char *input);
static int	export_query(t_list **env, const t_cmd *current_cmd);

int	msh_export(t_list **env, t_list **cmd, int index)
{
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	if (current_cmd == NULL || current_cmd->args[0] == NULL)
		return (1);
	if (current_cmd->args[1] == NULL)
		return (print_all_env_vars_with_prefix(env, "declare -x ",
				PRINT_EXPORT));
	return (export_query(env, current_cmd));
}

int	export_query(t_list **env, const t_cmd *current_cmd)
{
	char	*input;
	int		i;
	int		result;
	int		is_invalid;
	int		is_malloc_failure;

	i = 1;
	result = 0;
	is_malloc_failure = 0;
	while (current_cmd->args[i])
	{
		input = current_cmd->args[i];
		is_invalid = is_invalid_input(input);
		if (is_invalid == 0)
			is_malloc_failure = append_str_to_env(env, input);
		if (is_invalid == 1)
			result = 1;
		if (is_malloc_failure != 0)
			return (is_malloc_failure);
		i++;
	}
	return (result);
}

int	is_invalid_input(char *input)
{
	char	*pos_of_eq;

	pos_of_eq = ft_strchr(input, '=');
	if (pos_of_eq == NULL)
	{
		if (input[0] != 0 && calc_key_len(input) == (int) ft_strlen(input))
			return (NO_ERR_BUT_QUIT);
		else
		{
			ft_putstr_fd(input, 2);
			ft_putendl_fd(": not a valid identifier", 2);
			return (1);
		}
	}
	if (calc_key_len(input) == 0 \
		|| calc_key_len(input) + (pos_of_eq[-1] == '+') != pos_of_eq - input)
	{
		ft_putstr_fd(input, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (1);
	}
	return (0);
}
