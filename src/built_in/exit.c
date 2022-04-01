/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:02:48 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/04/01 15:58:09 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (1);
		else
			exit_value = ft_atoi(current_cmd->args[1]);
	}
	ft_lstclear(env, free_dict_entry);
	ft_lstclear(cmd, free_cmd);
	ft_putendl_fd("exit", 2);
	exit(exit_value);
}

unsigned char	are_arguments_ok(int i, const t_cmd *current_cmd)
{
	if (ft_strlen(current_cmd->args[1]) >= 20)
	{
		ft_putendl_fd("exit\nexit: numeric argument required", 2);
		exit (2);
	}
	if ((current_cmd->args[1][0] != '-' || current_cmd->args[1][0] != '+'))
		i++;
	while (current_cmd->args[1][i])
	{
		if (ft_isdigit(current_cmd->args[1][i]) == 0)
		{
			ft_putendl_fd("exit\nexit: numeric argument required", 2);
			exit (2);
		}
		i++;
	}
	if (current_cmd->args[2] != NULL)
	{
		ft_putendl_fd("exit\nexit: too many arguments", 2);
		return (1);
	}
	return (0);
}
