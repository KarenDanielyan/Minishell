/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 01:24:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/12 01:48:41 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

void	nodel_pop(t_nodel **head, t_nodel *to_pop)
{
	t_nodel	*prev;

	if (to_pop)
	{
		prev = nodel_prev(*head, to_pop);
		if (prev)
			prev->next = to_pop->next;
		if (*head == to_pop)
			*head = to_pop->next;
		to_pop->next = NULL;
		drop(NULL, to_pop->node);
		free(to_pop);
	}
}

t_nodel	*nodel_prev(t_nodel *head, t_nodel *current)
{
	while (head && head->next != current)
		head = head->next;
	return (head);
}
