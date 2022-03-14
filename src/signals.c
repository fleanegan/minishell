#include "minishell.h"



void	handle_ctrl_c(int signal_no, siginfo_t *info, void *hmm)
{
	printf(".. implement ctrl c\n");
	(void) signal_no;
	(void) info;
	(void) hmm;
	exit(1);
}

void	handle_ctrl_d(int signal_no, siginfo_t *info, void *hmm)
{
	printf(".. implement ctrl d\n");
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void	handle_ctrl_backslash(int signal_no, siginfo_t *info, void *hmm)
{
	printf(".. implement ctrl \\\n");
	(void) signal_no;
	(void) info;
	(void) hmm;
}


int	set_signal_handler(int signal_no,
					   void (*handler_function)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof act);
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler_function;
	act.sa_flags = SA_SIGINFO;
	return (sigaction(signal_no, &act, NULL));
}
