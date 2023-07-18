/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:32:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/18 22:35:31 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <stdio.h>

static t_node	*alloc_and_check(void);

t_node	*new_pipeline_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = PipelineNode;
	node->value.pipeline.in_fd = FD_INIT;
	node->value.pipeline.out_fd = FD_INIT;
	node->value.pipeline.left = left;
	node->value.pipeline.right = right;
	return (node);
}

t_node	*new_command_node(t_cmdtype type, t_node *prefix, t_node *command)
{
	t_node	*node;

	node = alloc_and_check();
	node->is_last = 1;
	node->type = CommandNode;
	node->value.cmd.in_fd = FD_INIT;
	node->value.cmd.out_fd = FD_INIT;
	node->value.cmd.type = type;
	node->value.cmd.prefix = prefix;
	node->value.cmd.command = command;
	return (node);
}

t_node	*new_scommand_node(t_node *word, t_node *suffix)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = SimpleCommandNode;
	node->value.s_cmd.in_fd = FD_INIT;
	node->value.s_cmd.out_fd = FD_INIT;
	node->value.s_cmd.word = word;
	node->value.s_cmd.suffix = suffix;
	return (node);
}

t_node	*new_ccommand_node(t_node *list, t_node *suffix)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = CompoundCommandNode;
	node->value.c_cmd.in_fd = FD_INIT;
	node->value.c_cmd.out_fd = FD_INIT;
	node->value.c_cmd.list = list;
	node->value.c_cmd.suffix = suffix;
	return (node);
}

static t_node	*alloc_and_check(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	node->is_last = LAST_INIT;
	return (node);
}
