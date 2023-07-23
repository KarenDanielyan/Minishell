/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:07:34 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/23 14:20:01 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>

int	my_fork(t_control *ctl)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror(EPERROR);
		lst_set(ctl->var_list, SHELL, ECODE, FAIL);
		ctl->execute = EXIT_FAILURE;
		printf("%d\n", *(ctl->estat));
	}
	return (pid);
}
