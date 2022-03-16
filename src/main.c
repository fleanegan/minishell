#include "minishell.h"

#ifndef IS_TEST

int	main(void)
{
	char	*line;
	char	*line_expanded;
	t_list	*env;
	t_list	*cmd;
	t_list	*tmp;

	env = init();
	if (env == NULL)
		return (1);
	ft_lstclear(&env, free_dict_entry);
	while (42)
	{
		line = readline("minishell$");
		if (! line)
		{
			handle_ctrl_d(-1, NULL, NULL);
			return (0);
		}
		add_history(line);
		line_expanded = expand_all_variables(env, line);
		cmd = parsing(line_expanded);
		tmp = cmd;
		while (tmp)
		{
			printf("exec_name: %s\n", get_content(tmp)->exec_name);
			printf("infile: %s\n", get_content(tmp)->infile);
			printf("outfile: %s\n", get_content(tmp)->outfile);
			tmp = tmp->next;
		}
		//execution(get_content(cmd)->exec_name, get_content(cmd)->args, NULL);
	}
}


#endif
