/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:05:09 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:05:12 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execution(t_list *cmd, t_list *env, int nb_cmd)
{
	pid_t	pid;
	int		i;
	int		**fd;

	i = 0;
	fd = NULL;
	if (nb_cmd == 1 && get_built_in_function_pointer(cmd->content) != NULL)
		return (execute_built_in_parent(cmd, env, i, fd));
	pid = -2;
	fd = ft_tabnew_two(nb_cmd, 2);
	if (fd == NULL)
		return (ENOMEM);
	if (init_pipes(nb_cmd, fd) && close_before_exit_process(fd))
		return (errno);
	while (i < nb_cmd)
	{
		pid = execute_cmd_in_fork(cmd, env, i, fd);
		if (pid == -1)
			return (errno);
		i++;
	}
	return (tear_down_parent(nb_cmd, fd, pid));
}

int	execute_execve(t_list *env, t_list *cmd, int index)
{
	char	**env_char;
	void	*target;
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(cmd, index));
	target = get_built_in_function_pointer(current_cmd);
	if (target == NULL)
	{
		if (access(current_cmd->exec_name, X_OK) != 0 \
			|| ft_strchr(current_cmd->exec_name, '/') == NULL)
			return (errno);
		env_char = (char **) to_array(env, cpy_dict_to_str);
		set_sa_handler(SIGINT, NULL);
		set_sa_handler(SIGQUIT, NULL);
		execve(current_cmd->exec_name, current_cmd->args, env_char);
		free_2d_array((void **) env_char);
		return (errno);
	}
	return (((int (*)(t_list **, t_list **, int index))target) \
			(&env, &cmd, index));
}
