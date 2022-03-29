#include "../minishell.h"

int	msh_unset(t_list **env, t_cmd *cmd)
{
	t_list	*current;
	int		i;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		current = *env;
		while (current != NULL)
		{
			if (msh_strcmp((((t_dict_entry *)(current->content))->key), \
				cmd->args[i]) == 0\
				&& cmd->args[i][0] != '?')
			{
				ft_lstrmnode(env, current, free_dict_entry);
				break ;
			}
			current = current->next;
		}
		i++;
	}
	return (0);
}
