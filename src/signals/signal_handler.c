/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:01:51 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:01:53 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_ctrl_c(int signal_no, siginfo_t *info, void *hmm)
{
	g_is_ctrl_c = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void	handle_ctrl_c_no_redisplay(int signal_no, siginfo_t *info, void *hmm)
{
	g_is_ctrl_c = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void	handle_ctrl_c_heredoc(int signal_no, siginfo_t *info, void *hmm)
{
	g_is_ctrl_c = 1;
	close(STDIN_FILENO);
	printf("\n");
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void	handle_ctrl_bs(int signal_no, siginfo_t *info, void *hmm)
{
	printf("\b\b  \b\b");
	g_is_ctrl_c = 2;
	(void) signal_no;
	(void) info;
	(void) hmm;
}
