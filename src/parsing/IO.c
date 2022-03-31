#include "../minishell.h"

int	is_file_created_successfully(char **file_name)
{
	int	fd;

	if (access(*file_name, W_OK) != 0)
	{
		fd = open(*file_name, O_WRONLY | O_CREAT, 0666);
		if (fd >= 3)
		{
			if (close(fd) == -1)
			{
				free(*file_name);
				file_name = NULL;
				return (1);
			}
			return (1);
		}
	}
	free(*file_name);
	return (0);
}

char	*new_enumerated_empty_file(char *prefix_file_name, int sequence)
{
	char	*file_name;
	char	*suffix_name;

	while (++sequence)
	{
		suffix_name = ft_itoa(sequence);
		file_name = append_str(ft_strdup(prefix_file_name), suffix_name, \
			(int)ft_strlen(suffix_name));
		free(suffix_name);
		if (file_name == NULL)
			break ;
		if (is_file_created_successfully(&file_name))
			return (file_name);
	}
	return (NULL);
}
