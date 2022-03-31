#include "../inc/minishell.h"

#ifndef IS_TEST

static int	user_input_to_cmd_list(t_list **env, t_list **cmd);
static int	write_pipe_line_result_into_env(\
			t_list **env, t_list **cmd, int pipe_line_result);

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	t_list	*cmd;
	int		pipe_line_result;

	env = init(envp);
	cmd = NULL;
	if (env == NULL)
		return (1);
	while (1)
	{
		if (user_input_to_cmd_list(&env, &cmd))
			continue ;
		pipe_line_result = execution(cmd, env, ft_lstsize(cmd));
		if (write_pipe_line_result_into_env(&env, &cmd, pipe_line_result))
			return (ENOMEM);
		ft_lstclear(&cmd, free_cmd);
	}
	(void) argc;
	(void) argv;
}

int	write_pipe_line_result_into_env(\
	t_list **env, t_list **cmd, int pipe_line_result)
{
	char	*pipe_line_result_as_char;

	pipe_line_result_as_char = ft_itoa(pipe_line_result);
	if (pipe_line_result_as_char == NULL)
	{
		ft_lstclear(cmd, free_cmd);
		ft_lstclear(env, free_dict_entry);
		free(pipe_line_result_as_char);
		return (1);
	}
	update_env(env, "?", pipe_line_result_as_char, ENV_REPLACE_VAR);
	free(pipe_line_result_as_char);
	return (0);
}

int	user_input_to_cmd_list(t_list **env, t_list **cmd)
{
	char	*line;
	char	*line_expanded;
	int		result;

	line = readline("minishell$ ");
	if (! line)
	{
		result = ft_atoi(get_entry_by_key(*env, "?")->value);
		ft_lstclear(cmd, free_cmd);
		ft_lstclear(env, free_dict_entry);
		printf("exit\n");
		exit (result);
	}
	add_history(line);
	line_expanded = expand_all_variables((*env), line);
	(*cmd) = parse(line_expanded, (*env));
	if (*cmd == NULL)
	{
		update_env(env, "?", "1", ENV_REPLACE_VAR);
		return (1);
	}
	free(line_expanded);
	return (0);
}

#endif
