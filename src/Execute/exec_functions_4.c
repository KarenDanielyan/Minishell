/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:53:34 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 13:04:59 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <libft.h>

static int	execute_nodel(t_control *ctl, t_nodel *head);

int	execute_prefix(t_control *ctl, t_node *self)
{
	t_nodel	*prefix;

	prefix = self->value.prefix;
	return (execute_nodel(ctl, prefix));
}

int	execute_suffix(t_control *ctl, t_node *self)
{
	t_nodel	*suffix;

	suffix = self->value.suffix;
	return (execute_nodel(ctl, suffix));
}

static int	execute_nodel(t_control *ctl, t_nodel *head)
{
	while (head)
	{
		if (execute(ctl, head->node) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
