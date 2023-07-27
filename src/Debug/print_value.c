/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:22:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/27 16:14:23 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_word_node(t_wordl *head);
static void	print_pipe(t_node *self);
static void	print_list(t_node *self);
static void	print_io(t_node *self);

void	print_value(t_node *node)
{
	if (node)
	{
		printf(": ");
		if (node->type == ListNode)
			print_list(node);
		else if (node->type == PipelineNode)
			print_pipe(node);
		else if (node->type == IORedirectNode)
			print_io(node);
		else if (node->type == WordNode)
			print_word_node(node->value.word);
	}
	printf("\n");
}

static void	print_list(t_node *self)
{
	if (self->value.list.type == AND)
		printf("\033[37m{%s}\033[0m", AND_IF);
	else
		printf("\033[37m{%s}\033[0m", OR_IF);
}

static void	print_pipe(t_node *self)
{
	printf("\033[37m{%d -> %d}\033[0m", \
		self->value.pipeline.in_fd, self->value.pipeline.out_fd);
}

static void	print_io(t_node *self)
{
	if (self->value.io.type == IN)
		printf("\033[37m%c\033[0m", LESS);
	if (self->value.io.type == OUT)
		printf("\033[37m%c\033[0m", GREAT);
	if (self->value.io.type == APPEND)
		printf("\033[37m%s\033[0m", DGREAT);
	if (self->value.io.type == HERE)
		printf("\033[37m%s\033[0m", DLESS);
	printf(" \033[37m[%d]\033[0m", self->value.io.fd);
}

void	print_word_node(t_wordl *head)
{
	while (head)
	{
		printf("\033[37m{%s}\033[0m → ", head->word->value);
		head = head->next;
	}
	printf("NULL");
}
