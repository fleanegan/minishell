#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->exec_name = NULL;
	cmd->args = NULL;
	cmd->redir_file_name = NULL;
	cmd->token = EMPTY;
	return (cmd);
}

t_list *parsing(const char *input)
{
	t_list	*result;

	result = ft_lstnew(new_cmd());
	if (result == NULL || result->content == NULL)
	{
		ft_lstclear(&result, &free_cmd);
		return (NULL);
	}
	get_content(result)->exec_name = (char *) input;
	return (result);
}


