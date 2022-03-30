#include "../minishell.h"

void	exec_child_heredoc(t_list *env, const char *delimiter, \
		char *(*line_reader)(const char *), const char *file_name);

int	g_is_ctrl_c = 0;

char	*new_enumerated_empty_file(char *prefix_file_name, int sequence)
{
	int		fd;
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
		if (access(file_name, W_OK) != 0)
		{
			fd = open(file_name, O_WRONLY | O_CREAT, 0666);
			if (fd >= 3)
			{
				if (close(fd) == -1)
					break ;
				return (file_name);
			}
		}
		free(file_name);
	}
	return (NULL);
}

char	*generate_heredoc(\
		t_list *env, const char *delimiter, char *(line_reader)(const char *))
{
	char	*file_name;
	int		wait_result_buffer;
	int		last_result;
	pid_t	pid;

	last_result = 0;
	file_name = new_enumerated_empty_file("/tmp/.minishell_heredoc", 0);
	pid = fork();
	if (pid == 0)
		exec_child_heredoc(env, delimiter, line_reader, file_name);
	if (pid == -1 || set_sa_handler(SIGINT, SIG_IGN) || last_result)
	{
		free(file_name);
		return (NULL);
	}
	if (pid > 0)
	{
		waitpid(pid, &wait_result_buffer, 0);
		if (set_signal_handler(SIGINT, handle_ctrl_c))
			exit(errno);
		if (WIFEXITED(wait_result_buffer))
			last_result = WEXITSTATUS(wait_result_buffer);
	}

	return (file_name);
}

void	exec_child_heredoc(t_list *env, const char *delimiter, \
		char *(*line_reader)(const char *), const char *file_name)
{
	int		fd;
	char	*heredoc;

	if (set_signal_handler(SIGINT, handle_ctrl_c_heredoc))
		exit(errno);
	heredoc = fetch_heredoc_input(env, delimiter, line_reader);
	if (heredoc == NULL)
		exit (1);
	fd = open(file_name, O_WRONLY);
	if (fd >= 3)
	{
		ft_putstr_fd(heredoc, fd);
		if (close(fd) != 0)
			exit(errno);
	}
	free(heredoc);
	exit(0);
}

char	*fetch_heredoc_input(\
		t_list *env, const char *string, char *(line_reader)(const char *))
{
	char	*result;
	char	*line;

	result = ft_strdup("");
	line = NULL;
	while (42)
	{
		line = line_reader(">");
		if (line == NULL) // && g_var
		{
			if (g_is_ctrl_c == 0)
			{
				printf("\nExpected %s as delimiter, but got ctrl-D\n", string);
				return (result);
			}
			free(result);
			return (NULL);
		}
		if (ft_strncmp(line, string, \
		calc_max_unsigned(ft_strlen(line), ft_strlen(string))) == 0)
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
