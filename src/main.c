#include "minishell.h"

void show_list(t_list *lst)
{
	puts("printing env");
	while (lst)
	{
		ft_putstr_fd(((t_dict_entry *)lst->content)->key, 1);
		lst = lst->next;
	}
}
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
	if (env == NULL)
		return (1);
	printf("-%s-\n", get_path(ft_strdup("ls"), ft_strdup("test:re")));//get_value_by_key(env, "$PATH")->value));
	while (0)
	{
		line = readline("minishell$");
		if (! line)
		{
			handle_ctrl_d(-1, NULL, NULL);
			return (0);
		}
		add_history(line);
		line_expanded = expand_all_variables(env, line);
		cmd = parsing(line_expanded, env);
//		tmp = cmd;
//		while (tmp)
//		{
//			printf("exec_name: %s\n", get_content(tmp)->exec_name);
//			printf("intoken: %d\n", get_content(tmp)->intoken);
//			printf("outtoken: %d\n", get_content(tmp)->outtoken);
//			printf("infile: %s\n", get_content(tmp)->infile);
//			printf("outfile: %s\n", get_content(tmp)->outfile);
//			printf("\n");
//			tmp = tmp->next;
//		}
		execution(cmd, NULL);
		ft_lstclear(&cmd, free_cmd);
	}
}


#endif
