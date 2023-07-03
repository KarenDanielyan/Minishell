/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:29:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/03 21:17:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <stdio.h>

static t_node	*alloc_and_check(void);

t_node	*new_list_node(t_ListType type, t_node *left, t_node *right)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = ListNode;
	node->value.list.type = type;
	node->value.list.left = left;
	node->value.list.right = right;
	return (node);
}

static t_node	*alloc_and_check(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	return (node);
}
