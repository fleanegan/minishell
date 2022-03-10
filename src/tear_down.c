#include "minishell.h"

void	free_cmd(void *cmd)
{
	if (cmd == NULL)
		return ;
	free(((t_cmd *) cmd)->exec_name);
	free_2d_array((void **) ((t_cmd *) cmd)->args);
	free(((t_cmd *) cmd)->redir_file_name);
	free(cmd);
}
