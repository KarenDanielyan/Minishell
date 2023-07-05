/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:25:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 02:50:39 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

static void	drop_prime(t_node *node);

void	drop(t_node *node)
{
	if (node->type == ListNode)
	{
		drop(node->value.list.left);
		drop(node->value.list.right);
	}
	else if (node->type == PipelineNode)
	{
		drop(node->value.pipeline.left);
		drop(node->value.pipeline.right);
	}
	else if (node->type == CommandNode)
	{
		drop(node->value.cmd.prefix);
		drop(node->value.cmd.command);
	}
	else
		drop_prime(node);
	free(node);
	return ;
}

static void	drop_prime(t_node *node)
{
	if (node->type == CompoundCommandNode)
	{
		drop(node->value.c_cmd.list);
		drop(node->value.c_cmd.suffix);
	}
	else if (node->type == SimpleCommandNode)
	{
		drop(node->value.s_cmd.word);
		drop(node->value.s_cmd.suffix);
	}
	else if (node->type == CmdPrefixNode)
		node_list_drop(node->value.prefix);
	else if (node->type == CmdSuffixNode)
		node_list_drop(node->value.suffix);
	else if (node->type == IORedirectNode)
		drop(node->value.io.filename);
	else if (node->type == WordNode)
		wordl_clear(node->value.word);
	else if (node->type == ErrorNode)
		free(node->value.error);
}
