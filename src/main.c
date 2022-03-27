#include "minishell.h"

void	print_cmd(t_list	*cmd)
{
	int	i;

	while (cmd != NULL)
	{
		printf("-----------------------------------------------------------\n");
		i = 0;
		printf("execname : %s\ninfile : %s\noutfile : %s\nintoken : %d\nouttoken : %d\npipe : %d\n", \
			get_content(cmd)->exec_name, get_content(cmd)->infile, \
			get_content(cmd)->outfile, get_content(cmd)->intoken, \
			get_content(cmd)->outtoken, get_content(cmd)->pipe);
		while (get_content(cmd)->args[i] != NULL)
		{
			printf("arg[%d] = %s\n", i, get_content(cmd)->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
	printf("-----------------------------------------------------------\n");
}

#ifndef IS_TEST

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*line_expanded;
	t_list	*env;
	t_list	*cmd;
	t_list	*tmp;

	(void) tmp;
	env = init(envp);
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
//		print_cmd(cmd);
		free(line_expanded);
		if (cmd != NULL)
		{
			char *tmp1 = ft_itoa(execution(cmd, env, ft_lstsize(cmd)));
			if (tmp1 == NULL)
			{
				ft_lstclear(&cmd, free_cmd);
				ft_lstclear(&env, free_dict_entry);
				free(line);
				return (1);
			}
			update_env(&env, "?", tmp1, ENV_REPLACE_VAR);
			free(tmp1);
		}
		ft_lstclear(&cmd, free_cmd);
	}
	(void) argc;
	(void) argv;
}

#endif
