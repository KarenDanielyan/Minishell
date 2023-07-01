/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:13:45 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/02 02:13:49 by kdaniely         ###   ########.fr       */
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

	if (*scanner && ((*scanner)->type == AND_OP || (*scanner)->type == OR_OP))
	{
		if ((*scanner)->type == AND_OP)
			type = AND;
		else
			type = OR;
		token_consume(scanner);
		pipeline = parsePipeline(scanner);
		return (parseListPrime(scanner, new_ListNode(type, expr, pipeline)));
	}
	else
		return (expr);
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
		pipeline_last(&(head->value.pipeline))->next = new_NodeList(parseCommand(scanner));
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