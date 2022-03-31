/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:05:04 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:05:06 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_pipes(int nb_processes, int **fd)
{
	int	i;

	i = 0;
	while (i < nb_processes)
	{
		pipe(fd[i]);
		i++;
	}
}

int	redirect_stdout_into_pipe(int *fd_of_pipe)
{
	if (ft_close(&fd_of_pipe[0]))
		return (1);
	if (dup2(fd_of_pipe[1], STDOUT_FILENO) == -1)
		return (1);
	if (ft_close(&fd_of_pipe[1]))
		return (1);
	return (0);
}

int	redirect_stdin_into_pipe(int *fd_of_pipe)
{
	if (ft_close(&fd_of_pipe[1]))
		return (1);
	if (dup2(fd_of_pipe[0], STDIN_FILENO) == -1)
		return (1);
	if (ft_close(&fd_of_pipe[0]))
		return (1);
	return (0);
}

int	redirect_infile_to_stdin(char *infile)
{
	int	fd;

	if (access(infile, R_OK) == 0)
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1 || dup2(fd, 0) == -1)
			return (errno);
	}
	else
		return (errno);
	return (0);
}

int	redirect_stdout_to_outfile(char *outfile, t_token mode)
{
	int	fd;

	if (mode == REDIR_OUT_REPLACE)
		fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1 || dup2(fd, 1) == -1)
		return (errno);
	return (0);
}
