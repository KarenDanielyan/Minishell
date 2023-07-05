/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:13:45 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/05 19:48:15 by kdaniely         ###   ########.fr       */
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
		expr->is_last = 0;
		pipeline->is_last = 1;
		return (parse_list_prime(scanner, new_list_node(type, expr, pipeline)));
	}
	else
		return (expr);
}

t_node	*parse_pipeline(t_token **scanner)
{
	t_node	*command;

	command = parse_command(scanner);
	return (parse_pipeline_prime(scanner, command));
}

t_node	*parse_pipeline_prime(t_token **scanner, t_node *expr)
{
	t_node	*command;

	if (*scanner && (*scanner)->type == OP_PIPE)
	{
		token_consume(scanner);
		command = parse_command(scanner);
		expr->is_last = 0;
		command->is_last = 1;
		return (parse_pipeline_prime(scanner, \
			new_pipeline_node(expr, command)));
	}
	else
		return (expr);
}

void	token_consume(t_token **scanner)
{
	t_token	*token;

	token = (*scanner);
	(*scanner) = (*scanner)->next;
	if (*scanner)
		(*scanner)->prev = NULL;
	wordl_clear(token->wordl);
	free(token);
}
