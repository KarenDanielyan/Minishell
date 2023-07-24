/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ecode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:20:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/24 15:58:45 by kdaniely         ###   ########.fr       */
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
		stat = 128 + WTERMSIG(*(ctl->estat));
		if (after_exec == TRUE)
		{
			if (WTERMSIG(*(ctl->estat)) == SIGQUIT)
				ft_putstr_fd("Quit\n", STDERR_FILENO);
			if (WTERMSIG(*(ctl->estat)) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	else
		stat = WEXITSTATUS(*(ctl->estat));
	s = ft_itoa(stat);
	lst_set(ctl->var_list, SHELL, ECODE, s);
	free(s);
}
