/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:32:28 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/12 14:24:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

t_list	*lst_get_by_key(t_list *var_list, char *key)
{
	while (var_list)
	{
		if (ft_strcmp(key, var_list->key) == 0)
			return (var_list);
		var_list = var_list->next;
	}	
	return (NULL);
}

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
