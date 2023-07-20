/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:07:34 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 22:20:01 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>

int	my_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
