#include "minishell.h"

t_cmd	*get_content(t_list *in)
{
	if (in == NULL)
		return (NULL);
	return (((t_cmd *)((in)->content)));
}
