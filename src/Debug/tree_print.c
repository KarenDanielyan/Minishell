/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:22:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 02:21:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "parser.h"

/* Pretty printing functions */
static void	print_tree_prime_two(t_node *node, char *ident);
static void	print_tree_prime(t_node *node, char *ident);
static char	*get_node_type(t_nodetype type);
static int	is_last(t_node *node);

void	print_tree(t_node *node, char *ident, int last)
{
	char	*marker;
	
	if (last)
		marker = "└──";
	else
		marker = "├──";
	printf ("%s%s%s\n", ident, marker, get_node_type(node->type));
	if (last)
		ident = ft_strjoin(ident, "     ");
	else
		ident = ft_strjoin(ident, "|    ");
	print_tree_prime(node, ident);
	free(ident);
}

static void print_tree_prime(t_node *node, char *ident)
{
	if (node->type == ListNode)
	{
		print_tree(node->value.list.left, ident, is_last(node));
		print_tree(node->value.list.right, ident, is_last(node));
	}
	else if (node->type == PipelineNode)
	{
		print_tree(node->value.pipeline.left, ident, is_last(node));
		print_tree(node->value.pipeline.right, ident, is_last(node));
	}
	else if (node->type == CommandNode)
	{
		print_tree(node->value.cmd.prefix, ident, is_last(node));
		print_tree(node->value.cmd.command, ident, is_last(node));
	}
	else if (node->type == SimpleCommandNode)
	{
		print_tree(node->value.s_cmd.word, ident, is_last(node));
		print_tree(node->value.s_cmd.suffix, ident, is_last(node));
	}
	else
		print_tree_prime_two(node, ident);
}

static void print_tree_prime_two(t_node *node, char *ident)
{
	t_nodel	*tmp;

	if (node->type == CompoundCommandNode)
	{
		print_tree(node->value.c_cmd.list, ident, is_last(node));
		print_tree(node->value.c_cmd.suffix, ident, is_last(node));
	}
	else if (node->type == CmdPrefixNode || node->type == CmdSuffixNode)
	{
		tmp = node->value.prefix;
		while (tmp)
		{
			print_tree(tmp->node, ident, is_last(tmp->node));
			tmp = tmp->next;
		}
	}
	else if (node->type == IORedirectNode)
		print_tree(node->value.io.filename, ident, is_last(node->value.io.filename));
}

static int	is_last(t_node *node)
{
	if (node->type == WordNode || node->type == CmdSuffixNode 
		|| node->type == SimpleCommandNode || node->type == CompoundCommandNode)
		return (1);
	else
		return (0);
}

static char *get_node_type(t_nodetype type)
{
	if (type == ListNode)
		return ("ListNode");
	if (type == PipelineNode)
		return ("PipelineNode");
	if (type == CommandNode)
		return ("CommandNode");
	if (type == SimpleCommandNode)
		return ("SimpleCommandNode");
	if (type == CompoundCommandNode)
		return ("CompoundCommandNode");
	if (type == IORedirectNode)
		return ("IORedirectNode");
	if (type == CmdPrefixNode)
		return ("CmdPrefixNode");
	if (type == CmdSuffixNode)
		return ("CmdSuffixNode");
	if (type == WordNode)
		return ("WordNode");
	return (NULL);
}
