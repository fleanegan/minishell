#include "minishell.h"

void	free_cmd(void *cmd)
{
	if (cmd == NULL)
		return ;
	free(get_content(cmd)->exec_name);
	free_2d_array((void **) get_content(cmd)->args);
	free(get_content(cmd)->redir_file_name);
	free(cmd);
}
