/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:03:04 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:03:06 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	msh_pwd(t_list **env, t_list **cmd, int index)
{
	char			*pwd;
	char			s[2048];
	t_dict_entry	*tmp;

	pwd = getcwd(s, 2048);
	if (pwd == NULL)
	{
		tmp = get_entry_by_key(*env, "PWD");
		if (tmp != NULL)
		{
			ft_putendl_fd(tmp->value, 1);
			return (0);
		}
		perror("pwd");
		return (errno);
	}
	ft_putendl_fd(pwd, 1);
	return (0);
	(void) cmd;
	(void) index;
}
