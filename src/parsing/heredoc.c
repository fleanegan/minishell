#include "../minishell.h"

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
	char	*heredoc;
	int		fd;
	int		wait_result_buffer;
	int last_result;

	file_name = new_enumerated_empty_file("/tmp/.minishell_heredoc", 0);
	pid_t pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("could not fork", 2);
		free(file_name);
		return (NULL);
	}
	if (set_signal_handler(SIGINT, handle_ctrl_c_parent))
	{
		ft_putendl_fd("handler could not be set", 2);
		exit(errno);
	}
	if (pid == 0)
	{
		if (set_signal_handler(SIGINT, handle_ctrl_c_heredoc))
		{
			ft_putendl_fd("handler could not be set", 2);
			exit(errno);
		}
		ft_putendl_fd("in heredoc fork. waiting for input", 2);
		heredoc = fetch_heredoc_input(env, delimiter, line_reader);
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
	waitpid(pid, &wait_result_buffer, 0);
	if (set_signal_handler(SIGINT, handle_ctrl_c))
	{
		ft_putendl_fd("handler could not be set", 2);
		exit(errno);
	}
	//puts("after fork");
	if (WIFEXITED(wait_result_buffer))
		last_result = WEXITSTATUS(wait_result_buffer);
	else
		last_result = 0;
	if (last_result)
	{
		free(file_name);
		file_name = NULL;
	}
	fprintf(stderr, "filename: <%s>\n", file_name);
	return (file_name);
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
		if (line == NULL)
		{
			puts("got empty line");
			free(result);
			return (0);
		}
		// TODO: free_and_return_on_handle_ctrl
		if (ft_strncmp(line, string, \
		calc_max_unsigned(ft_strlen(line), ft_strlen(string))) == 0)
		{
			free(line);
			return (result);
		}
		result = expand_all_variables(env,\
		append_str(result, line, ft_strlen(line)));
		result = append_str(result, "\n", 1);
		free(line);
	}
}
