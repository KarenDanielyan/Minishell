/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:13:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/03 16:48:13 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

static void		nodelist_push(t_nodel **head, t_nodel *to_push);
static t_node	*parse_helper(t_token **scanner);

t_node	*parse_prefix(t_token **scanner)
{
	return (parse_helper(scanner));
}

t_node	*parse_suffix(t_token **scanner)
{
	return (parse_helper(scanner));
}

t_node	*parse_word(t_token **scanner)
{
	t_token	*word_token;
	
	word_token = NULL;
	token_consume(scanner); // TODO: Instead of this this should be like this word_token = token_consume(scanner);
	return (new_WordNode(word_token->wordl));
}

t_node	*parse_helper(t_token **scanner)
{
	t_nodel	node_list;

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