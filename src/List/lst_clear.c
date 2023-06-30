/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:26:31 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/30 18:05:34 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief		Deletes and frees the given node and every successor
 * 				of that node, using the function `del` and free().
 * 				Finally, the pointer to the list is set to NULL.
 * 
 * @param lst	A linked list.
 * @param del	Deletion function pointer.
 */
void	lst_clear(t_list **lst, void (*del)(void *))
{
	t_list	*a;

	if (lst)
	{
		while (*lst)
		{
			a = (*lst)->next;
			if ((*lst)->joined)
				del((*lst)->joined);
			if ((*lst)->key)
				del((*lst)->key);
			if ((*lst)->value)
				del((*lst)->value);
			free(*lst);
			*lst = a;
		}
	}
}
