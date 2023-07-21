/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:10:00 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 17:54:16 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_wordl *cmd, t_control *ctl)
{
	t_list	*temp;

	(void)cmd;
	temp = ctl->var_list;
	while (temp)
	{
		if (temp->type == EXPORT && ft_strchr(temp->joined, EQUALS))
		{
			printf("%s=", temp->key);
			if (temp->value)
				printf("%s", temp->value);
			printf("\n");
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
