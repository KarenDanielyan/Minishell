/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:20:23 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 02:37:14 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <stdio.h>

static t_node	*alloc_and_check(void);

t_node	*new_error_node(char *msg)
{
	t_node	*node;

	node = alloc_and_check();
	node->is_last = 1;
	node->type = ErrorNode;
	node->value.error = ft_strdup(msg);
	return (node);
}

t_node	*parse_error(t_token *scanner)
{
	char	*str;
	t_word	*word;
	t_node	*node;

	if (!scanner)
		str = ft_strdup(ERROR_EOL);
	else
	{
		word = wordl_join(scanner->wordl);
		str = ft_strjoin(ERROR_MSG, word->value);
		ft_strappend(&str, SQUOTE);
		word_delete(word);
	}
	node = new_error_node(str);
	free(str);
	return (node);
}

static t_node	*alloc_and_check(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	node->is_last = -42;
	return (node);
}
