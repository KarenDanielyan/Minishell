/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:29 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/07 18:12:02 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void my_exit(char *status)
{
	int i;

	i = 0;
	
	if(status[0] >= '0' && status[0] <= '9')
		exit(ft_atoi(status));
	printf("bash: exit: %s numeric argument required\n",ft_strjoin(status,":"));
}