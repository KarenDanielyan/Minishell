/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:10:00 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/16 18:36:04 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		if (temp->type == EXPORT && ft_strchr(temp->joined, EQUALS))
		{
			printf("%s=", temp->key);
			if(temp->value)
				printf("%s", temp->value);
			printf("\n");
		}
		temp = temp->next;
	}
}
