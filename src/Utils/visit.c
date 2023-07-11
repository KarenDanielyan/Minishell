/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:42:04 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/12 01:21:33 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	visit_prime(t_control *ctl, t_node *self, \
	void (*op)(t_control *ctl, t_node *self));
static void	visit_prime2(t_control *ctl, t_node *self, \
	void (*op)(t_control *ctl, t_node *self));

/**
 * @brief	visit() function is the traversal function for
 * 			the generated abstract syntax tree.
 * 			function pointer op point to the function to be
 * 			executed on the node self.
 */
void	visit(t_control *ctl, t_node *self, \
	void (*op)(t_control *ctl, t_node *self))
{	
	if (self)
	{
		visit_prime(ctl, self, op);
		op(ctl, self);
	}
	return ;
}

static void	visit_prime(t_control *ctl, t_node *self, \
	void (*op)(t_control *ctl, t_node *self))
{
	if (self->type == ListNode)
	{
		visit(ctl, self->value.list.left, op);
		visit(ctl, self->value.list.right, op);
	}
	else if (self->type == PipelineNode)
	{
		visit(ctl, self->value.pipeline.left, op);
		visit(ctl, self->value.pipeline.right, op);
	}
	else if (self->type == CommandNode)
	{
		visit(ctl, self->value.cmd.prefix, op);
		visit(ctl, self->value.cmd.command, op);
	}
	else if (self->type == CompoundCommandNode)
	{
		visit(ctl, self->value.c_cmd.list, op);
		visit(ctl, self->value.c_cmd.suffix, op);
	}
	else
		visit_prime2(ctl, self, op);
}

static void	visit_prime2(t_control *ctl, t_node *self, \
	void (*op)(t_control *ctl, t_node *self))
{
	if (self->type == SimpleCommandNode)
	{
		visit(ctl, self->value.s_cmd.word, op);
		visit(ctl, self->value.s_cmd.suffix, op);
	}
	else if (self->type == CmdPrefixNode)
		nodel_visit(ctl, self->value.prefix, op);
	else if (self->type == CmdSuffixNode)
		nodel_visit(ctl, self->value.suffix, op);
	else if (self->type == IORedirectNode)
		visit(ctl, self->value.io.filename, op);
	else if (self->type == WordNode)
		return ;
}
