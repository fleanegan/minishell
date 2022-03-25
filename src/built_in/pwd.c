#include "../minishell.h"

int	msh_pwd(t_list **env, t_cmd *cmd)
{
	t_dict_entry	*pwd;

	(void) cmd;
	pwd = get_value_by_key(*env, "PWD");
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd->value, 1);
	return (0);
}
