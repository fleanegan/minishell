#include "minishell.h"

void handle_ctrl_c(int signal_no, siginfo_t *info, void *hmm)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void handle_ctrl_c_parent(int signal_no, siginfo_t *info, void *hmm)
{
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void handle_ctrl_c_heredoc(int signal_no, siginfo_t *info, void *hmm)
{
	printf("heredoc child handler active\n");
	close(STDIN_FILENO);
//	exit(0);
	(void) signal_no;
	(void) info;
	(void) hmm;
}

int set_signal_handler(int signal_no,
					   void (*handler_function)(int, siginfo_t *, void *))
{
	struct sigaction act;

	ft_memset(&act, 0, sizeof act);
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler_function;
	act.sa_flags = SA_SIGINFO;
	if (signal_no == SIGQUIT)
		act.sa_handler = SIG_IGN;
	return (sigaction(signal_no, &act, NULL));
}

