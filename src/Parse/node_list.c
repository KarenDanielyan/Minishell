/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:34:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 02:48:19 by kdaniely         ###   ########.fr       */
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

t_nodel	*new_node_list(t_node *node)
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

void	node_list_drop(t_nodel *list)
{
	t_nodel	*tmp;

	while (list)
	{
		tmp = list->next;
		drop(list->node);
		free(list);
		list = tmp;
	}
}

void	node_list_check_syntax(t_nodel *list, int *visit)
{
	t_nodel	*tmp;

	while (list)
	{
		tmp = list->next;
		check_syntax_prime(list->node, visit);
		free(list);
		list = tmp;
	}
}
