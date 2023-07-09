/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:10:00 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/09 21:43:25 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		if (temp->type == EXPORT)
		{
			printf("%s=", temp->key);
			if (temp->value)
				printf("%s", temp->value);
			printf("\n");
		}
		temp = temp->next;
	}
}
