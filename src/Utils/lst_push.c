/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:01:31 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/30 21:44:17 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdio.h>
/*
*	Reference: DNE
*
*	Description: Adds the node ’new’ at the beginning of the list.
*
*	Return value: None
*/
void	lst_push_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		new->next = *lst;
		new->prev = NULL;
		(*lst)->prev = new;
		*lst = new;
	}
}

/*
*	Reference: DNE
*
*	Description: Adds the node ’new’ at the end of the list.
*
*	Return Value: None
*/
void	lst_push_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = lst_last(*lst);
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}

void	lst_push_on(t_list **lst, t_list *new, int loc)
{
	t_list	*loc_node;

	loc_node = NULL;
	if (loc <= lst_size(*lst))
	{
		loc_node = get_node(*lst, loc);
		new->prev = loc_node;
		new->next = loc_node->next;
		loc_node->next = new;
		if (loc != lst_size(*lst))
			(new->next)->prev = new;
	}
}
