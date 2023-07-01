/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:13:45 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/02 01:54:43 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

t_Node	*parseList(t_token **scanner)
{
	t_Node	*pipeline;

	pipeline = parsePipeline(scanner);
	return (parseListPrime(scanner, pipeline));
}

t_Node	*parseListPrime(t_token **scanner, t_Node *expr)
{
	t_ListType	type;
	t_Node		*pipeline;

	if (*scanner && (*scanner)->type == AND_IF || (*scanner)->type == OR_IF)
	{
		if ((*scanner)->type == AND_IF)
			type = AND;
		else
			type = OR;
		token_consume(scanner);
		pipeline = parsePipeline(scanner);
		return (parseListPrime(scanner, new_ListNode(type, expr, pipeline)));
	}
}

static t_PipelineNode	*pipeline_last(t_PipelineNode *head);

t_Node	*parsePipeline(t_token **scanner)
{
	t_Node	*head;
	t_Node	*command;

	command = parseCommand(scanner);
	head = new_PipelineNode(command);
	while ((*scanner)->type == PIPE_OP)
	{
		token_consume(scanner);
		pipeline_last(head->value.pipeline)->next = parseCommand(scanner);
	}
	return (head);
}

static t_PipelineNode	*pipeline_last(t_PipelineNode *head)
{
	if (head)
	{
		while (head->next)
			head = head->next;
	}
	return (head);
}