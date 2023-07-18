/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:34:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/18 22:26:39 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>

t_nodel	*nodel_last(t_nodel *head)
{
	if (head)
	{
		while (head->next)
			head = head->next;
	}
	return (head);
}

t_nodel	*nodel_new(t_node *node)
{
	t_nodel	*nodel;

	nodel = (t_nodel *)malloc(sizeof(t_nodel));
	if (!node)
	{
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	nodel->node = node;
	nodel->next = NULL;
	return (nodel);
}

void	nodel_clear(t_nodel *list, void (*del)(t_node *node))
{
	t_nodel	*tmp;

	while (list)
	{
		tmp = list->next;
		if (del)
			del(list->node);
		free(list);
		list = tmp;
	}
}

void	nodel_check_syntax(t_nodel *list, void (*check)(t_node *node))
{
	while (list)
	{
		if (check)
			check(list->node);
		list = list->next;
	}
}

void	nodel_visit(t_control *ctl, t_nodel *list, \
	void (*op)(t_control *ctl, t_node *self))
{
	while (list)
	{
		visit(ctl, list->node, op);
		list = list->next;
	}
}
