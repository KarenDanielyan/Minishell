/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:00:54 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/08 02:40:19 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "debug.h"

/**
 * @brief	parse() consumes the sequence of tokens and returns
 * 			an abstract syntax tree on successfull parsing.
 * 
 * 			If parsing encounters an error, it wil set the err flag as 1,
 * 			indicating that syntax error was encountered during parsing.
*/
void	*parse(t_token *scanner, t_list *var_list)
{
	t_node	*node;
	int		err;

	err = 0;
	node = parse_list(&scanner, &err);
	print_tree(node, "", 1);
	if (err != 0)
	{
		visit(node, check_syntax);
		visit(node, drop);
		lst_set(var_list, "?", "2");
		node = NULL;
	}
	return ((void *)node);
}
