#include "../minishell.h"

int	parse_exec_name(\
	t_list *env, t_list *current_cmd, t_list **arg_tmp, t_string_slice *sub)
{
	char			*raw_exec_name;
	t_dict_entry	*path;
	char			**exec_name;

	exec_name = &get_content(current_cmd)->exec_name;
	raw_exec_name = parse_until(sub, ft_isspace);
	path = get_entry_by_key(env, "PATH");
	if (path != NULL)
		*exec_name = get_path(raw_exec_name, path->value);
	else
		*exec_name = ft_strdup(raw_exec_name);
	if (*exec_name == NULL)
		return (1);
	append_new_arg(arg_tmp, raw_exec_name);
	return (0);
}

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
		res = ft_calloc(len_path(path + i) + 2, sizeof(char));
		if (res == NULL)
			return (ft_strdup(exec_name));
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
	return (ft_strdup(exec_name));
}
