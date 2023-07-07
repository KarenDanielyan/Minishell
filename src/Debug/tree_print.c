/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:22:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/07 16:43:31 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "parser.h"

/* Pretty printing functions */
static void	print_tree_prime_three(t_node *node, char *ident);
static void	print_tree_prime_two(t_node *node, char *ident);
static void	print_tree_prime(t_node *node, char *ident);

void		print_value(t_node	*node);

void	print_tree(t_node *node, char *ident, int last)
{
	char	*marker;

	if (last)
		marker = "└──";
	else
		marker = "├──";
	if (node)
	{
		printf ("%s%s%s", ident, marker, get_node_type(node->type));
		print_value(node);
	}
	else
	{
		printf("%s%s%s\n", ident, marker, " NULL");
		return ;
	}
	if (last)
		ident = ft_strjoin(ident, "     ");
	else
		ident = ft_strjoin(ident, "|    ");
	print_tree_prime(node, ident);
	free(ident);
}

static void	print_tree_prime(t_node *node, char *ident)
{
	if (!node)
		return ;
	if (node->type == ListNode)
	{
		print_tree(node->value.list.left, ident, \
			is_last(node->value.list.left));
		print_tree(node->value.list.right, ident, \
			is_last(node->value.list.right));
	}
	else if (node->type == PipelineNode)
	{
		print_tree(node->value.pipeline.left, ident, \
			is_last(node->value.pipeline.left));
		print_tree(node->value.pipeline.right, ident, \
			is_last(node->value.pipeline.right));
	}
	else if (node->type == CommandNode)
	{
		print_tree(node->value.cmd.prefix, ident, \
			is_last(node->value.cmd.prefix));
		print_tree(node->value.cmd.command, ident, \
			is_last(node->value.cmd.command));
	}
	else
		print_tree_prime_two(node, ident);
}

static void	print_tree_prime_two(t_node *node, char *ident)
{
	if (node->type == SimpleCommandNode)
	{
		print_tree(node->value.s_cmd.word, ident, \
			is_last(node->value.s_cmd.word));
		print_tree(node->value.s_cmd.suffix, ident, \
			is_last(node->value.s_cmd.suffix));
	}
	else if (node->type == CompoundCommandNode)
	{
		print_tree(node->value.c_cmd.list, ident, \
			is_last(node->value.c_cmd.list));
		print_tree(node->value.c_cmd.suffix, ident, \
			is_last(node->value.c_cmd.suffix));
	}
	else
		print_tree_prime_three(node, ident);
}

static void	print_tree_prime_three(t_node *node, char *ident)
{
	t_nodel	*tmp;

	if (node->type == CmdPrefixNode || node->type == CmdSuffixNode)
	{
		tmp = node->value.prefix;
		while (tmp)
		{
			print_tree(tmp->node, ident, is_last(tmp->node));
			tmp = tmp->next;
		}
	}
	else if (node->type == IORedirectNode)
		print_tree(node->value.io.filename, ident, \
			is_last(node->value.io.filename));
}
