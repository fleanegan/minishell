/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:05:20 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:05:22 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	**ft_tabnew_two(int col, int line)
{
	int	i;
	int	**tab;

	i = 0;
	if (!col || !line)
		return (0);
	tab = ft_calloc(col + 1, sizeof(int *));
	if (!tab)
		return (0);
	while (i < col)
	{
		tab[i] = malloc(line * sizeof(int));
		if (! tab[i])
			return (0);
		i++;
	}
	return (tab);
}

int	ft_close(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
			return (1);
		*fd = -1;
	}
	return (0);
}

int	close_before_exit_process(int **fd)
{
	int	i;

	i = 0;
	if (fd == NULL)
		return (0);
	while (fd[i] != NULL)
	{
		if (fd[i][0] != -1)
		{
			if (ft_close(&fd[i][0]) == 1)
				return (errno);
		}
		if (fd[i][1] != -1)
		{
			if (ft_close(&fd[i][1]) == 1)
				return (errno);
		}
		i++;
	}
	return (errno);
}

void	*get_built_in_function_pointer(const t_cmd *content)
{
	int						i;
	size_t					max;
	const t_built_in_entry	built_in_array[NB_BUILT_INS] = {\
			{"env", msh_env}, \
			{"cd", msh_cd}, \
			{"export", msh_export}, \
			{"echo", msh_echo}, \
			{"pwd", msh_pwd}, \
			{"exit", msh_exit}, \
			{"unset", msh_unset} \
			};

	i = 0;
	while (i < NB_BUILT_INS)
	{
		max = calc_max_unsigned(\
		ft_strlen(content->args[0]), \
		ft_strlen(built_in_array[i].name));
		if (ft_strncmp(content->args[0], built_in_array[i].name, max) == 0)
			return (built_in_array[i].func_ptr);
		i++;
	}
	return (NULL);
}
