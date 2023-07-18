/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:50:38 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/18 22:33:50 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <stdio.h>

static t_node	*alloc_and_check(void);

t_node	*new_io_redirect_node(t_IOType type, t_node *filename)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = IORedirectNode;
	node->value.io.fd = FD_INIT;
	node->value.io.type = type;
	node->value.io.filename = filename;
	return (node);
}

t_node	*new_prefix_node(t_nodel *value)
{
	t_node	*node;

	node = alloc_and_check();
	node->is_last = 0;
	node->type = CmdPrefixNode;
	node->value.prefix = value;
	return (node);
}

t_node	*new_suffix_node(t_nodel *value)
{
	t_node	*node;

	node = alloc_and_check();
	node->is_last = 1;
	node->type = CmdSuffixNode;
	node->value.suffix = value;
	return (node);
}

t_node	*new_word_node(t_wordl *word)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = WordNode;
	node->value.word = word;
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
