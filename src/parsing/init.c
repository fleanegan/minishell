/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:04:04 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:04:19 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->exec_name = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->intoken = EMPTY;
	cmd->outtoken = EMPTY;
	cmd->pipe = EMPTY;
	return (cmd);
}

int	append_new_cmd(t_list **result_cmd, t_list **current_cmd)
{
	t_cmd	*tmp;

	tmp = new_cmd();
	ft_lstadd_back(result_cmd, ft_lstnew(tmp));
	*current_cmd = ft_lstlast((*result_cmd));
	if (*current_cmd == NULL || (*current_cmd)->content == NULL)
	{
		ft_lstclear(result_cmd, &free_cmd);
		return (ENOMEM);
	}
	return (0);
}

int	append_new_arg(t_list **tmp_args, char *arg_str)
{
	t_list	*tmp;

	tmp = ft_lstnew(arg_str);
	if (tmp == NULL || arg_str == NULL)
	{
		ft_lstclear(tmp_args, &free_cmd);
		return (ENOMEM);
	}
	ft_lstadd_back(tmp_args, tmp);
	return (0);
}
