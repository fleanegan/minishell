#include "../minishell.h"

char	*get_home_path(t_list *const *env);

int	msh_cd(t_list **env, t_list **cmd, int index)
{
	t_cmd	*current_cmd;
	char	s[2048];
	char	*dest_path;

	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	if (current_cmd->args[1] == NULL)
		dest_path = get_home_path(env);
	else
		dest_path = current_cmd->args[1];
	if (dest_path == NULL)
		return (1);
	if (chdir(dest_path) == -1)
	{
		perror(dest_path);
		return (errno);
	}
	if (update_env(env, "PWD", getcwd(s, 2048), ENV_REPLACE_VAR))
		return (1);
	return (0);
}

char	*get_home_path(t_list *const *env)
{
	t_dict_entry	*home;

	home = get_entry_by_key(*env, "HOME");
	if (home == NULL)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (NULL);
	}
	return (home->value);
}
