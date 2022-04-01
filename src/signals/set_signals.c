/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:01:51 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:01:53 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_signal_handler(int signal_no, \
	void (*handler_function)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof act);
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler_function;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	return (sigaction(signal_no, &act, NULL));
}

int	set_sa_handler(int signal_no, __sighandler_t test)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof act);
	sigemptyset(&act.sa_mask);
	act.sa_handler = test;
	return (sigaction(signal_no, &act, NULL));
}