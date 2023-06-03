/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:10:00 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/03 19:28:05 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env(t_list *env)
{
	t_list *temp;

	temp = env;
	while (temp)
	{
		printf("%s\n",temp->joined);
		temp = temp->next;
	}
}