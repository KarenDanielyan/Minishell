/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:10:00 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/26 15:42:11 by kdaniely         ###   ########.fr       */
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
		if (temp->type == EXPORT && temp->joined \
			&& ft_strchr(temp->joined, EQUALS))
		{
			printf("%s=", temp->key);
			if (temp->value)
				printf("%s", temp->value);
			printf("\n");
		}
		temp = temp->next;
	}
	estat_set(ctl->estat, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
