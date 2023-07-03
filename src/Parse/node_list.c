/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:34:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/03 21:09:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <stdio.h>

t_nodel	*list_last(t_nodel *head)
{
	if (head)
	{
		while (head->next)
			head = head->next;
	}
	return (head);
}

t_nodel		*new_node_list(t_node *node)
{
	t_nodel	*nodel;

	nodel = (t_nodel *)malloc(sizeof(t_nodel));
	if (!node)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	nodel->node = node;
	nodel->next = NULL;
	return (nodel);
}
