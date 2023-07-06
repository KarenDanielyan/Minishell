/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:34:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 16:25:34 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	while (list)
	{
		check_syntax_prime(list->node, visit);
		list = list->next;
	}
}

void	node_list_visit(t_nodel *list, void (*op)(t_node *self))
{
	while (list)
	{
		visit(list->node, op);
		list = list->next;
	}
}
