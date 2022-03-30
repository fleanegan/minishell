#include "../minishell.h"

int	msh_pwd(t_list **env, t_list **cmd, int index)
{
	char	*pwd;
	char	s[2048];

	pwd = getcwd(s, 2048);
	if (pwd == NULL)
	{
		perror("pwd");
		return (errno);
	}
	ft_putendl_fd(pwd, 1);
	return (0);
	(void) cmd;
	(void) env;
	(void) index;
}
