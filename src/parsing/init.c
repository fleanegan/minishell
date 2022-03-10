#include "../minishell.h"

t_cmd *new_cmd(void)
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

int append_new_cmd(t_list **result_cmd, t_list **current_cmd)
{
	ft_lstadd_back(result_cmd, ft_lstnew(new_cmd()));
	*current_cmd = ft_lstlast((*result_cmd));
	if (*current_cmd == NULL || (*current_cmd)->content == NULL)
	{
		ft_lstclear(result_cmd, &free_cmd);
		return (1);
	}
	return (0);
}
