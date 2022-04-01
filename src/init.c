/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:00:02 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:00:10 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_env(t_list **env, char **envp)
{
	if (envp == NULL)
		return (0);
	while (*envp)
	{
		if (append_str_to_env(env, *envp))
		{
			ft_putendl_fd("error while parsing envp", 2);
			ft_lstclear(env, free_dict_entry);
			return (1);
		}
		envp++;
	}
	return (0);
}

t_list	*init(char **envp)
{
	t_list	*result;

	result = NULL;
	if (set_signal_handler(SIGINT, handle_ctrl_c) \
		|| set_signal_handler(SIGQUIT, NULL))
	{
		ft_putendl_fd("error in init", 2);
		return (NULL);
	}
	if (update_env(&result, "?", "0", ENV_REPLACE_VAR) \
		|| init_env(&result, envp) == 1)
	{
		ft_putendl_fd("error initiating msh_env", 2);
		ft_lstclear(&result, free_dict_entry);
		return (NULL);
	}
	return (result);
}
