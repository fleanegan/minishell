#include "minishell.h"

int	len_path(char *path)
{
	int	i;

	i = 0;
	if (path == NULL)
		return (0);
	while (path[i] && path[i] != ':')
	{
		if (path[i] == 0)
			return (i);
		i++;
	}
	return (i);
}

char	*get_path(char *exec_name, char *path)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (len_path(path + i) != 0)
	{
		free(res);
		res = NULL;
		res = ft_calloc(len_path(path) + 2, sizeof(char));
		ft_strlcpy(res, path + i, len_path(path + i) + 1);
		res[len_path(path + i)] = '/';
		res = append_str(res, exec_name, ft_strlen(exec_name));
		i += len_path(path + i);
		if (path[i] == ':')
			i++;
		if (access(res, X_OK) == 0)
			return (res);
	}
	free(res);
	return (exec_name);
}
