/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:42:04 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/07 21:10:53 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	visit_prime(t_node *self, void (*op)(t_node *self));
static void	visit_prime2(t_node *self, void (*op)(t_node *self));

/**
 * @brief	visit() function is the traversal function for
 * 			the generated abstract syntax tree.
 * 			function pointer op point to the function to be
 * 			executed on the node self.
 */
void	visit(t_node *self, void (*op)(t_node *self))
{	
	if (self)
	{
		visit_prime(self, op);
		op(self);
	}
	return ;
}

static void	visit_prime(t_node *self, void (*op)(t_node *self))
{
	if (self->type == ListNode)
	{
		visit(self->value.list.left, op);
		visit(self->value.list.right, op);
	}
	else if (self->type == PipelineNode)
	{
		visit(self->value.pipeline.left, op);
		visit(self->value.pipeline.right, op);
	}
	else if (self->type == CommandNode)
	{
		visit(self->value.cmd.prefix, op);
		visit(self->value.cmd.command, op);
	}
	else if (self->type == CompoundCommandNode)
	{
		visit(self->value.c_cmd.list, op);
		visit(self->value.c_cmd.suffix, op);
	}
	else
		visit_prime2(self, op);
}

static void	visit_prime2(t_node *self, void (*op)(t_node *self))
{
	if (self->type == SimpleCommandNode)
	{
		visit(self->value.s_cmd.word, op);
		visit(self->value.s_cmd.suffix, op);
	}
	else if (self->type == CmdPrefixNode)
		node_list_visit(self->value.prefix, op);
	else if (self->type == CmdSuffixNode)
		node_list_visit(self->value.suffix, op);
	else if (self->type == IORedirectNode)
		visit(self->value.io.filename, op);
	else if (self->type == WordNode)
		return ;
}
