/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ecode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:20:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 15:20:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <sys/wait.h>

void	set_ecode(t_control *ctl, int after_exec)
{
	int		stat;
	char	*s;

	if (WIFSIGNALED(*(ctl->estat)) && WTERMSIG(*(ctl->estat)) != SIGPIPE)
	{
		if (WTERMSIG(*(ctl->estat)) == SIGINT)
			stat = SIGHUP;
		else
			stat = 0;
		if (after_exec == TRUE)
		{
			stat = 128 + WTERMSIG(*(ctl->estat));
			if (WTERMSIG(*(ctl->estat)) == SIGQUIT)
				ft_dprintf(STDERR_FILENO, "Quit: %d\n", WTERMSIG(*(ctl->estat)));
			if (WTERMSIG(*(ctl->estat)) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	else if (after_exec == TRUE)
		stat = WEXITSTATUS(*(ctl->estat));
	else
		stat = *(ctl->estat) >> 8;
	s = ft_itoa(stat);
	lst_set(ctl->var_list, SHELL, ECODE, s);
	free(s);
}
