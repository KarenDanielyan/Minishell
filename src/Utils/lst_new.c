/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:34:03 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/28 18:08:26 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

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

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
	{
		perror("malloc");
		return (NULL);
	}
	split = ft_split(key_val, ASSIGN_OP);
	new->joined = key_val;
	new->key = split[0];
	new->value = split[1];
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
