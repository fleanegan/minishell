#include "../minishell.h"

int	msh_echo(t_list **env, t_list **cmd, int index)
{
	int		i;
	int		nl_flag;
	int		is_behind_options;
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	nl_flag = 1;
	is_behind_options = 0;
	i = 1;
	while (current_cmd->args[0] && current_cmd->args[i] && *env)
	{
		if (current_cmd->args[i][0] == '-' && is_behind_options == 0 \
			&& msh_strcmp(current_cmd->args[i], "-n\0") == 0)
				nl_flag = 0;
		else
		{
			if (is_behind_options)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(current_cmd->args[i], 1);
			is_behind_options = 1;
		}
		i++;
	}
	if (nl_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
