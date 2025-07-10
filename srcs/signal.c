/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:56:26 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/10 18:41:02 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_exit_status = 0;

void	signal_handler(int x)
{
	(void)x;
	g_exit_status = 130;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	dfl_parent_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler_heredoc1(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		close(0);
	}
}

void	signal_handler_heredoc(void)
{
	signal(SIGINT, signal_handler_heredoc1);
	signal(SIGQUIT, SIG_IGN);
}
