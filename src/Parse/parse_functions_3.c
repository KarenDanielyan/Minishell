/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:13:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/02 16:39:36 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

static void	nodelist_push(t_nodelist **head, t_nodelist *to_push);

t_node	*parse_prefix(t_token **scanner)
{
	t_nodelist	*node_list;
	
	node_list = NULL;
	while ((*scanner)->type == IO_FILE || (*scanner)->type == IO_APPEND
		|| (*scanner)->type == IO_HERE)
		nodelist_push(&node_list, new_NodeList(parse_ioredirect(scanner)));
}

t_node	*parse_suffx(t_token **scanner)
{
	t_nodelist	node_list;

	node_list = NULL;
	while ((*scanner)->type == IO_FILE || (*scanner)->type == IO_APPEND
		|| (*scanner)->type == IO_HERE || (*scanner)->type == WORD)
	{
		if ((*scanner)->type == WORD)
			nodelist_push(&node_list, new_NodeList(parse_word(scanner)));
		else
			nodelist_push(&node_list, new_NodeList(parse_ioredirect(scanner)));
	}
}

static void	nodelist_push(t_nodelist **head, t_nodelist *to_push)
{
	if (head)
	{
		if (*head)
			list_last(*head)->next = to_push;
		else
			*head = to_push;
	}
}