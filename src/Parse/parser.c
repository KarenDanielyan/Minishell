/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:00:54 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/07 21:08:15 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "debug.h"

void	*parse(t_token *scanner)
{
	t_node	*node;
	int		err;

	err = 0;
	node = parse_list(&scanner, &err);
	print_tree(node, "", 1);
	return ((void *)node);
}
