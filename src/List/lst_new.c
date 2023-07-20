/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:34:03 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 23:27:39 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>
#include <stdio.h>

/**
 * @brief New node function
 * 
 * @param type		Variable type
 * @param key_val	String containing the key and the value
 * @param prev		previous node of the list
 * @param next		The next node of the list
 * @return			Returns the newly allocated node.
 */
t_list	*lst_new(int type, char *key_val)
{
	t_list	*new;
	char	**split;

	split = NULL;
	new = NULL;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
	{
		perror(EPERROR);
		return (NULL);
	}
	new->key = NULL;
	new->value = NULL;
	split = ft_split(key_val, EQUALS);
	new->joined = key_val;
	if (split[0])
	{
		new->key = ft_strdup(split[0]);
		if (split[1])
			new->value = ft_strdup(split[1]);
	}
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	free_2d(split);
	return (new);
}
