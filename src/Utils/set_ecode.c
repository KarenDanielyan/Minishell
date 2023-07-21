/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ecode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:20:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/21 02:17:05 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <sys/wait.h>

void	set_ecode(t_control *ctl)
{
	int		stat;
	char	*s;

	if (WIFSIGNALED(ctl->estat))
	{
		stat = 128 + WTERMSIG(ctl->estat);
		if (WTERMSIG(ctl->estat) == SIGQUIT)
			ft_putstr_fd("Quit", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		stat = WEXITSTATUS(ctl->estat);
	s = ft_itoa(stat);
	lst_set(ctl->var_list, SHELL, ECODE, s);
	free(s);
}
