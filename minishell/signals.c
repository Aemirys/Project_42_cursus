/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:36:00 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 10:24:49 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_code = 0;

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_exit_code = 130;
	}
}

void	sigint_nl_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	quit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit\n", 5);
		g_exit_code = 131;
	}
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_nl_handler);
	signal(SIGQUIT, SIG_IGN);
}
