#include "../minishell.h"

int	msh_echo(t_list *env, t_cmd *cmd)
{
	int		i;
	int		nl_flag;
	int		is_behind_options;

	nl_flag = 1;
	is_behind_options = 0;
	i = 1;
	while (cmd->args[0] && cmd->args[i] && env)
	{
		if (cmd->args[i][0] == '-' && is_behind_options == 0 \
			&& msh_strcmp(cmd->args[i], "-n\0") == 0)
				nl_flag = 0;
		else
		{
			if (is_behind_options)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(cmd->args[i], 1);
			is_behind_options = 1;
		}
		i++;
	}
	if (nl_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
