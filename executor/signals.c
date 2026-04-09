/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:55:14 by msnizek           #+#    #+#             */
/*   Updated: 2026/04/08 23:48:08 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	event_hook(void)
{
	if (g_sig == SIGINT)
		rl_done = 1;
	return (0);
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = event_hook;
}

int	child_setup_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (perror("SIGINT"), 1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (perror("SIGQUIT"), 1);
	return (0);
}
