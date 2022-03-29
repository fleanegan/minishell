#include "../minishell.h"

int	msh_exit(t_list **env, t_list **tmp, int index)
{
	int exit_value;
	int i;
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(*tmp, index));
	i = 0;
	if (current_cmd->args[1])
	{
		exit_value= ft_atoi(current_cmd->args[1]);
		if (current_cmd->args[2] != NULL)
			ft_putendl_fd("exit: too many arguments", 2);
		else
			while (current_cmd->args[1][i])
			{
				if (ft_isdigit(current_cmd->args[1][i]))
					ft_putendl_fd("exit: numeric argument required", 2);
				i++;
			}
		exit(exit_value);
	}
	exit(0);
	(void) env;
	return (errno);
}
