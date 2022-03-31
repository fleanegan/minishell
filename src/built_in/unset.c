/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:03:10 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:03:14 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	msh_unset(t_list **env, t_list **cmd, int index)
{
	t_list	*current;
	int		i;
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	if (current_cmd == NULL \
		|| current_cmd->args[1] == NULL || current_cmd->args[1][0] == '\0')
		return (0);
	i = 1;
	while (current_cmd->args[i] != NULL)
	{
		current = *env;
		while (current != NULL)
		{
			if (ft_strcmp((((t_dict_entry *)(current->content))->key), \
				current_cmd->args[i]) == 0 && current_cmd->args[i][0] != '?')
			{
				ft_lstrmnode(env, current, free_dict_entry);
				break ;
			}
			current = current->next;
		}
		i++;
	}
	return (0);
}
