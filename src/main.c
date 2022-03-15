#include "minishell.h"

char *generate_heredoc(t_list *env, const char *string);

#ifndef IS_TEST

int	main(void)
{
	//char	*result;
	t_list	*env;

	env = init();
	if (env == NULL)
		return (1);
	char	*heredoc = generate_heredoc(env, "EOF");
	printf("%s", heredoc);
	free(heredoc);
	ft_lstclear(&env, free_dict_entry);
//	while (42)
//	{
//		result = readline("minishell$");
//		if (! result)
//		{
//			handle_ctrl_d(-1, NULL, NULL);
//			return (0);
//		}
//		add_history(result);
//		execution(result, NULL, NULL);
//	}
}

char *generate_heredoc(t_list *env, const char *string)
{
	char	*result;
	char	*line;

	result = ft_strdup("");
	line = NULL;
	while (42)
	{
		line = readline(">");
		if (line == NULL)
		{
			handle_ctrl_d(-1, NULL, NULL);
			return (0);
		}
		if (ft_strncmp(line, string, calc_max_unsigned(ft_strlen(line), ft_strlen(string))) == 0)
		{
			free(line);
			return (result);
		}
		result = expand_all_variables(env, append_str(result, line, ft_strlen(line)));
		result = append_str(result, "\n", 1);
		free(line);
	}
	return (result);
	(void) env;
}
//		printf("line: >%s<, string: >%s<, result: >%s<\n", line, string, result);


#endif
