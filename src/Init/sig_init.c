/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:00:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/12 14:03:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_irc(int signum);

void	sig_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_irc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static void	ft_irc(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = -475836;
	}
}