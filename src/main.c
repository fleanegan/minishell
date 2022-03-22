#include "minishell.h"

#ifndef IS_TEST

int	main(void)
{
	char	*line;
	char	*line_expanded;
	t_list	*env;
	t_list	*cmd;
	t_list	*tmp;

	(void) tmp;
	env = init();
	cmd = NULL;
	if (env == NULL)
		return (1);
	while (1)
	{
		line = readline("minishell$ ");
		if (! line)
		{
			ft_lstclear(&cmd, free_cmd);
			ft_lstclear(&env, free_dict_entry);
			printf("exit\n");
			return (0);
		}
		add_history(line);
		line_expanded = expand_all_variables(env, line);
		cmd = parse(line_expanded, env);
		free(line_expanded);
		if (cmd != NULL)
		{
			char *tmp1 = ft_itoa(execution(cmd, NULL));
			if (tmp1 == NULL)
			{
				ft_lstclear(&cmd, free_cmd);
				ft_lstclear(&env, free_dict_entry);
				free(line);
				return (1);
			}
			update_env(&env, "?", tmp1);
			free(tmp1);
		}
		ft_lstclear(&cmd, free_cmd);
		free(line);
	}
}

#endif
