/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:13:45 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/02 15:37:58 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

t_node	*parse_list(t_token **scanner)
{
	t_node	*pipeline;

	pipeline = parse_pipeline(scanner);
	return (parse_list_prime(scanner, pipeline));
}

t_node	*parse_list_prime(t_token **scanner, t_node *expr)
{
	t_ListType	type;
	t_node		*pipeline;

	if (*scanner && ((*scanner)->type == AND_OP || (*scanner)->type == OR_OP))
	{
		if ((*scanner)->type == AND_OP)
			type = AND;
		else
			type = OR;
		token_consume(scanner);
		pipeline = parse_pipeline(scanner);
		return (parse_list_prime(scanner, new_ListNode(type, expr, pipeline)));
	}
	else
		return (expr);
}

static t_pipelinenode	*pipeline_last(t_pipelinenode *head);

t_node	*parse_pipeline(t_token **scanner)
{
	t_node	*head;
	t_node	*command;

	command = parse_command(scanner);
	head = new_PipelineNode(command);
	while ((*scanner)->type == PIPE_OP)
	{
		token_consume(scanner);
		list_last(&(head->value.pipeline))->next \
			= new_NodeList(parse_command(scanner));
	}
	return (head);
}

t_pipelinenode	*list_last(t_pipelinenode *head)
{
	if (head)
	{
		while (head->next)
			head = head->next;
	}
	return (head);
}
