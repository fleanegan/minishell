#include "../minishell.h"

void	write_heredoc_into_tmp_file(t_list *env, const char *delimiter, \
		char *(*line_reader)(const char *), const char *file_name);
char	*handle_events_inside_fetch_heredoc(const char *string, char *result);

int	g_is_ctrl_c = 0;

int is_file_created_successfully(char **file_name)
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

char	*generate_heredoc(\
		t_list *env, const char *delimiter, char *(line_reader)(const char *))
{
	char	*file_name;
	int		wait_result_buffer;
	pid_t	pid;

	file_name = new_enumerated_empty_file("/tmp/.minishell_heredoc", 0);
	pid = fork();
	if (pid == -1 || set_sa_handler(SIGINT, SIG_IGN) || file_name == NULL)
	{
		free(file_name);
		return (NULL);
	}
	if (pid == 0)
		write_heredoc_into_tmp_file(env, delimiter, line_reader, file_name);
	if (pid > 0)
	{
		waitpid(pid, &wait_result_buffer, 0);
		if (set_signal_handler(SIGINT, handle_ctrl_c) \
		|| (WIFEXITED(wait_result_buffer) && WEXITSTATUS(wait_result_buffer)))
		{
			free(file_name);
			return (NULL);
		}
	}
	return (file_name);
}

void	write_heredoc_into_tmp_file(t_list *env, const char *delimiter, \
		char *(*line_reader)(const char *), const char *file_name)
{
	int		fd;
	char	*heredoc;

	if (set_signal_handler(SIGINT, handle_ctrl_c_heredoc))
		exit(errno);
	heredoc = fetch_heredoc_input(env, (char *) delimiter, line_reader);
	if (heredoc == NULL)
		exit (1);
	fd = open(file_name, O_WRONLY);
	if (fd >= 3)
	{
		ft_putstr_fd(heredoc, fd);
		free(heredoc);
		heredoc = NULL;
		if (close(fd) != 0)
			exit(errno);
	}
	free(heredoc);
	exit(0);
}
// Todo: does not work with errno...

char	*fetch_heredoc_input(\
		t_list *env, char *delimiter, char *(line_reader)(const char *))
{
	char	*result;
	char	*line;

	result = ft_strdup("");
	line = NULL;
	while (42)
	{
		line = line_reader(">");
		if (line == NULL)
			return (handle_events_inside_fetch_heredoc(delimiter, result));
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (result);
		}
		result = expand_all_variables(env, \
		append_str(result, line, ft_strlen(line)));
		result = append_str(result, "\n", 1);
		free(line);
	}
}

char	*handle_events_inside_fetch_heredoc(const char *string, char *result)
{
	if (g_is_ctrl_c == 0)
	{
		ft_putstr_fd("Expected '", 2);
		ft_putstr_fd((char *) string, 2);
		ft_putstr_fd("' as delimiter, but got ctrl-D\n", 2);
		return (result);
	}
	free(result);
	return (NULL);
}
