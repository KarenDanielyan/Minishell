/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:01:31 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/28 18:07:51 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

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
