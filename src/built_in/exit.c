#include "../../inc/minishell.h"

unsigned char	are_arguments_ok(int i, const t_cmd *current_cmd);

int	msh_exit(t_list **env, t_list **cmd, int index)
{
	unsigned char	exit_value;
	int				i;
	t_cmd			*current_cmd;

	exit_value = 0;
	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	i = 0;
	if (current_cmd->args[1])
	{
		if (are_arguments_ok(i, current_cmd) != 0)
			exit_value = 2;
		else
			exit_value = ft_atoi(current_cmd->args[1]);
	}
	ft_lstclear(env, free_dict_entry);
	ft_lstclear(cmd, free_cmd);
	exit(exit_value);
}

unsigned char	are_arguments_ok(int i, const t_cmd *current_cmd)
{
	if (current_cmd->args[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	else
	{
		while (current_cmd->args[1][i])
		{
			if (ft_strlen(current_cmd->args[1]) >= 20 \
				|| (ft_isdigit(current_cmd->args[1][i]) == 0 \
					&& (current_cmd->args[1][0] != '-' \
					|| current_cmd->args[1][0] != '+')))
			{
				ft_putendl_fd("exit: numeric argument required", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
