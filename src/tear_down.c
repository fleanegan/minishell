#include "minishell.h"

void	free_cmd(void *cmd)
{
	if (cmd == NULL)
		return ;
	free(((t_cmd *) cmd)->exec_name);
	free_2d_array((void **) ((t_cmd *) cmd)->args);
	free(((t_cmd *) cmd)->infile);
	free(cmd);
}

void	free_dict_entry(void *dict_entry)
{
	if (dict_entry == NULL)
		return ;
	free(((t_dict_entry *) dict_entry)->value);
	free(((t_dict_entry *) dict_entry)->key);
	free(dict_entry);
}
