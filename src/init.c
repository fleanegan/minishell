#include "minishell.h"

int	init()
{
	if (set_signal_handler(SIGINT, handle_ctrl_c) \
		|| set_signal_handler(1, handle_ctrl_d) \
		|| set_signal_handler(SIGQUIT, handle_ctrl_backslash))
		return (1);
	return (0);
}