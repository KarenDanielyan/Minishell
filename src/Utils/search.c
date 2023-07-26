/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:03:58 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/25 22:26:30 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static t_node	*nodel_search(t_control *ctl, t_nodel *self, t_nodetype type);
static t_node	*search_prime2(t_control *ctl, t_node *self, t_nodetype type);
static t_node	*search_prime(t_control *ctl, t_node *self, t_nodetype type);

/**
 * @brief	search() traverses the tree to find a node with
 * 			the specified type.
 * 			Returns the first occurence of the node, NULL if
 * 			a node with the specified type does not exist.
*/
t_node	*search(t_control *ctl, t_node *self, t_nodetype type)
{
	if (!self)
		return (NULL);
	if (self->type == type)
		return (self);
	return (search_prime(ctl, self, type));
}

static t_node	*search_prime(t_control *ctl, t_node *self, t_nodetype type)
{
	t_node	*tmp;

	if (self->type == ListNode)
	{
		tmp = search(ctl, self->value.list.left, type);
		if (!tmp)
			return (search(ctl, self->value.list.right, type));
	}
	else if (self->type == PipelineNode)
	{
		tmp = search(ctl, self->value.pipeline.left, type);
		if (!tmp)
			return (search(ctl, self->value.pipeline.right, type));
		return (tmp);
	}
	else if (self->type == CommandNode)
	{
		tmp = search(ctl, self->value.cmd.prefix, type);
		if (!tmp)
			return (search(ctl, self->value.cmd.command, type));
		return (tmp);
	}
	return (search_prime2(ctl, self, type));
}

static t_node	*search_prime2(t_control *ctl, t_node *self, t_nodetype type)
{
	t_node	*tmp;

	if (self->type == CompoundCommandNode)
	{
		tmp = search(ctl, self->value.c_cmd.list, type);
		if (!tmp)
			return (search(ctl, self->value.c_cmd.suffix, type));
		return (tmp);
	}
	else if (self->type == SimpleCommandNode)
	{
		tmp = search(ctl, self->value.s_cmd.word, type);
		if (!tmp)
			return (search(ctl, self->value.s_cmd.suffix, type));
		return (tmp);
	}
	else if (self->type == CmdPrefixNode)
		return (nodel_search(ctl, self->value.prefix, type));
	else if (self->type == CmdSuffixNode)
		return (nodel_search(ctl, self->value.suffix, type));
	else if (self->type == IORedirectNode)
		return (search(ctl, self->value.io.filename, type));
	return (NULL);
}

static t_node	*nodel_search(t_control *ctl, t_nodel *self, t_nodetype type)
{
	t_nodel	*tmp;

	tmp = self;
	(void)ctl;
	while (tmp)
	{
		if (tmp->node->type == type)
			return (tmp->node);
		tmp = tmp->next;
	}
	return (NULL);
}
