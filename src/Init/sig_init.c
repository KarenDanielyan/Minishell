/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:00:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 19:56:32 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	ft_irc(int signum);

int	handler(void)
{
	return (0);
}

void	sig_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_irc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	rl_catch_signals = 0;
	rl_event_hook = &handler;
}

static void	ft_irc(int signum)
{
	g_estat = signum;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 42;
	}
}
