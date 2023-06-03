/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:32:28 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/03 14:30:37 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * @brief			Get the node of a linked list under the position `loc`.
 * 
 * @param lst		A linked list.
 * @param loc		Position of a node in a list.
 * @return t_list*	Pointer to the node in a list.
 */
t_list	*get_node(t_list *lst, int loc)
{
	if (lst && loc < lst_size(lst))
	{
		while (loc--)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}
