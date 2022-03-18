#include "minishell.h"

int	len_path(char *path)
{
	int	i;

	if (path == NULL)
		return (0);
	i = 0;
	while (path[i] && path[i] != ':')
	{
		if (path[i] == 0)
			return (0);
		i++;
	}
	return (i);
}

char	*get_path(char *exec_name, char *path)
{
	int		i;
	char	*res;

	i = 1;
	res = NULL;
	printf("path = %s\n", path);
	printf("len = %d\n", len_path(ft_strdup("")));
	while (0)
	{
		res = malloc(len_path(path + i) * sizeof(char) + 1);
		ft_strlcpy(res, path + i, len_path(path) + 1);
		res[len_path(res) - 1] = '/';
		res = append_str(res, exec_name, ft_strlen(exec_name));
		i += len_path(path + i + 1);
		printf("path = %s\n", path);
		printf("path + i = %s\n", path + i);
		free(res);
	}
	(void) i;
	(void) exec_name;
	(void) res;
	return (res);
}
