#include "minishell.h"

int	calc_strnlen_size(char *s1, char *s2)
{
	return ((int) calc_max_unsigned(\
		ft_strlen(s1), \
		ft_strlen(s2)));
}

int	msh_strcmp(char *s1, char *s2)
{
	int max;

	max = calc_strnlen_size(s1, s2);
	return (ft_strncmp(s1, s2, max));
}

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
	if (key == NULL || key[0] == 0 || key[0] == '_' || (ft_isalpha(key[0]) == 0 && key[0] != '?'))
		return (0);
	if (key[0] == '?')
		return (1);
	while (key[i] != 0 \
			&& (ft_isalnum(key[i])
			|| key[i] == '_'))
		i++;
	return (i);
}

t_dict_entry	*get_value_by_key(t_list *lst, char *key_without_dollar)
{
	size_t	max;

	while (lst != NULL && lst->content != NULL)
	{
		max = calc_max_unsigned(\
		ft_strlen(((t_dict_entry *) (lst->content))->key), \
		calc_key_len(key_without_dollar));
		if (ft_strncmp(((t_dict_entry *)(lst->content))->key, \
			key_without_dollar, max) == 0)
			return (lst->content);
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

int	cpy_str(void *content, void **result)
{
	(*result) = ft_strdup((char *)content);
	if (*result == NULL)
		return (1);
	return (0);
}

int	cpy_dict_to_str(void *content, void **result)
{
	t_dict_entry	*entry;

	entry = content;
	if (msh_strcmp(entry->key, "?") != 0)
	{
		(*result) = append_str(entry->key, "=", 1);
		(*result) = append_str(*result, entry->value, ft_strlen(entry->value));
		if (*result == NULL)
			return (1);
	}
	else
		*result = NULL;
	return (0);
}

void	*free_list_and_return_null(t_list **lst, void (*del)(void *))
{
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

int	is_token(int c)
{
	return (c == '>' || c == '<' || c == '|');
}
