#include "minishell.h"

int	**ft_tabnew_two(int col, int line)
{
	int	i;
	int	**tab;

	i = 0;
	if (!col || !line)
		return (0);
	tab = malloc(col * sizeof(int *));
	if (!tab)
		return (0);
	while (i < col)
	{
		tab[i] = malloc(line * sizeof(int));
		if (!tab)
			return (0);
		i++;
	}
	return (tab);
}

int	ft_destroy_tab_two(int **tab, int col)
{
	int	i;

	i = 0;
	if (!*tab)
		return (1);
	while (i < col)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

int ft_close(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
			return (1);
		*fd = -1;
	}
	return (0);
}

int	close_before_exit_process(int **fd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (fd[i][0] != -1)
		{
			if (ft_close(&fd[i][0]) == 1)
				return (1);
		}
		if (fd[i][1] != -1)
		{
			if (ft_close(&fd[i][1]) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
