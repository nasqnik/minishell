/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meid <meid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:28:02 by meid              #+#    #+#             */
/*   Updated: 2025/01/31 13:16:16 by meid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	disable_echoctl(void)
// {
// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		our_static("exit status", 1);
	}
}

void	castom_signals(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	castom_ing(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	castom_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		our_static("exit status", 1);
		close(STDIN_FILENO);
	}
}
