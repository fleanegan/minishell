#include "minishell.h"

t_cmd	*get_content(t_list *in)
{
	if (in == NULL)
		return (NULL);
	return (((t_cmd *)((in)->content)));
}

int	calc_key_len(char *key)
{
	int	i;

	i = 0;
	if (key == NULL || key[i] == 0 || ft_isdigit(key[i]))
		return (0);
	key++;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_' || key[i] == '?'))
		i++;
	return (i);
}

t_dict_entry	*get_value_by_key(t_list *lst, char *key)
{
	char	*key_without_dollar;
	size_t	max;

	key_without_dollar = key + 1;
	while (lst)
	{
		max = calc_max_unsigned(\
		ft_strlen(((t_dict_entry *) (lst->content))->key), \
		calc_key_len(key));
		if (ft_strncmp(((t_dict_entry *) (lst->content))->key, \
			key_without_dollar , max) == 0)
			return ((t_dict_entry *) (lst->content));
		lst = lst->next;
	}
	return (NULL);
}

char	*append_str(char *base, char *appendix, int appendix_size)
{
	int		base_size;
	char	*result;

	if (base == NULL || appendix == NULL)
		return (NULL);
	base_size = ft_strlen(base);
	result = ft_calloc((base_size + appendix_size + SPACE_FOR_NULLTERMIN), \
		sizeof(char));
	if (result == NULL)
	{
		free(base);
		return (NULL);
	}
	ft_strlcpy(\
	result, base, base_size + SPACE_FOR_NULLTERMIN);
	ft_strlcat(\
	result, appendix, base_size + appendix_size + SPACE_FOR_NULLTERMIN);
	free(base);
	return (result);
}

int cpy_str(void *content, void **result) {
	(*result) = ft_strdup((char *)content);
	if (*result == NULL)
		return (1);
	return (0);
}

void *free_list_and_return_null(t_list **lst, void (*del)(void *)) {
	ft_lstclear(lst, del);
	return (NULL);
}


char	*read_file(char *name)
{
	char	*result;
	char	*line;
	int		fd;

	fd = open(name, O_RDONLY);
	result = ft_strdup("");
	while (gnl(fd, &line) == 1)
	{
		result = append_str(result, line, (int)ft_strlen(line));
		free(line);
	}
	if (close(fd))
	{
		free(result);
		return (NULL);
	}
	return (result);
}