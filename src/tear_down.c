#include "minishell.h"

void	free_cmd(void *cmd)
{
	if (cmd == NULL)
		return ;
	free(((t_cmd *) cmd)->exec_name);
	free_2d_array((void **) ((t_cmd *) cmd)->args);
	free(((t_cmd *) cmd)->infile);
	free(((t_cmd *) cmd)->outfile);
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

int tear_down_one_command(t_list **arg_tmp)
{
	ft_lstclear(arg_tmp, free);
	return (1);
}
