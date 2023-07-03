/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:13:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 02:14:40 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

static void		nodelist_push(t_nodel **head, t_nodel *to_push);
static t_nodel	*parse_helper(t_token **scanner, int type);

t_node	*parse_prefix(t_token **scanner)
{
	t_nodel	*node_list;

	node_list = parse_helper(scanner, CmdPrefixNode);
	return (new_prefix_node(node_list));
}

t_node	*parse_suffix(t_token **scanner)
{
	t_nodel	*node_list;

	node_list = parse_helper(scanner, CmdSuffixNode);
	return (new_suffix_node(node_list));
}

t_node	*parse_word(t_token **scanner)
{
	t_wordl	*word_token;
	
	word_token = (*scanner)->wordl;
	(*scanner)->wordl = NULL;
	token_consume(scanner);
	return (new_word_node(word_token));
}

static t_nodel	*parse_helper(t_token **scanner, int type)
{
	t_nodel	*node_list;

	node_list = NULL;
	if (scanner && *scanner)
	{
		while (*scanner)
		{
			if ((*scanner)->type == IO_FILE ||(*scanner)->type == IO_APPEND \
				|| (*scanner)->type == IO_HERE)
				nodelist_push(&node_list, new_node_list(parse_word(scanner)));
			else if ((*scanner)->type == WORD && type == CmdSuffixNode)
				nodelist_push(&node_list, new_node_list(parse_ioredirect(scanner)));
			else
				break ;
		}
	}
	return (node_list);
}

static void	nodelist_push(t_nodel **head, t_nodel *to_push)
{
	if (head)
	{
		if (*head)
			list_last(*head)->next = to_push;
		else
			*head = to_push;
	}
}
