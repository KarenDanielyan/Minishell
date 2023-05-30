/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:32:28 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/30 15:59:47 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

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
