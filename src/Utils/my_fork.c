/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:07:34 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 17:22:27 by dohanyan         ###   ########.fr       */
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
		estat_set(ctl->estat, EXIT_FAILURE);
		ctl->execute = EXIT_FAILURE;
	}
	return (pid);
}
