/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:34:58 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/12 14:25:26 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

static void	lst_del(t_list *var_l)
{
	free(var_l->joined);
	free(var_l->key);
	free(var_l->value);
	free(var_l);
}

void	lst_pop(t_list **lst, t_list *to_pop)
{
	t_list	*next;
	t_list	*prev;

	if (to_pop)
	{
		next = to_pop->next;
		prev = to_pop->prev;
		lst_del(to_pop);
		if (lst && *lst)
		{
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
			if (*lst == to_pop)
				*lst = next;
		}
	}
}
