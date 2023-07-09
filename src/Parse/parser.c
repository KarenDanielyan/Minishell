/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:00:54 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/09 14:48:15 by dohanyan         ###   ########.fr       */
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
		visit(NULL, node, check_syntax);
		visit(NULL, node, drop);
		lst_set(var_list, "?", SYNTAX_ERR);
		node = NULL;
	}
	return ((void *)node);
}
