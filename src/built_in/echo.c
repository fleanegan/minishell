#include "../minishell.h"

int	calc_strnlen_size(char *s1, char *s2)
{
	return ((int) calc_max_unsigned(\
		ft_strlen(s1), \
		ft_strlen(s2)));
}

int	msh_strcmp(char *s1, char *s2)
{
	int max;

	max = calc_strnlen_size(s1, s2);
	return (ft_strncmp(s1, s2, max));
}

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
		if (cmd->args[i][0] == '-' && is_behind_options == 0)
		{
			if (msh_strcmp(cmd->args[i++], "-n") == 0)
				nl_flag = 0;
		}
		else
		{
			if (is_behind_options)
				ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(cmd->args[i++], STDOUT_FILENO);
			is_behind_options = 1;
		}
	}
	if (nl_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
