/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:01:31 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/07 17:08:49 by kdaniely         ###   ########.fr       */
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

/**
 * @brief		Adds the node 'new' into the position 'loc' in the list.
 * 
 * @param lst	The linked list.
 * @param new	The node to be added to the list.
 * @param loc	Index of the place where node should be added.
 * 
 * @note	The new node will be pushed as the next element of the node under
 * 			the index `loc`.
 */
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
