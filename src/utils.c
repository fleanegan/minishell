#include "minishell.h"

t_cmd	*get_content(t_list *in)
{
	return (((t_cmd *)((in)->content)));
}
