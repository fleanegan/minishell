#include "minishell.h"

int	execution(t_list *cmd, t_list *env, int nb_cmd)
{
	pid_t	pid;
	int		i;
	int		**fd;

	set_sa_handler(SIGINT, SIG_IGN);
	fd = ft_tabnew_two(nb_cmd, 2);
	init_pipes(nb_cmd, fd);
	i = 0;
	pid = -2;
	while (i < nb_cmd)
	{
		if (get_built_in_function_pointer(cmd->content) != NULL && nb_cmd == 1)
			return (execute_built_in_parent(cmd, env, i, fd));
		else
		{
			pid = execute_cmd_in_fork(cmd, env, i, fd);
			if (pid == -1)
				return (errno);
		}
		cmd = cmd->next;
		i++;
	}
	return (tear_down_parent(nb_cmd, fd, pid));
}

int	execute_execve(t_cmd *content, t_list *env)
{
	char	**env_char;
	void	*target;

	target = get_built_in_function_pointer(content);
	if (target == NULL)
	{
		if (access(content->exec_name, X_OK) != 0)
			return (errno);
		env_char = (char **) to_array(env, cpy_dict_to_str);
		set_sa_handler(SIGINT, NULL);
		execve(content->exec_name, content->args, env_char);
		free_2d_array((void **) env_char);
		return (errno);
	}
	return (((int (*)(t_list **, t_cmd *))target)(&env, content));
}
