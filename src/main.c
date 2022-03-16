#include "minishell.h"

#ifndef IS_TEST

int	main(void)
{
	//char	*result;
	t_list	*env;

	env = init();
	if (env == NULL)
		return (1);
	char	*heredoc = fetch_heredoc_input(env, "EOF", 0);
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


#endif
