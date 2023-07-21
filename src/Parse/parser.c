/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:00:54 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/21 02:16:43 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "debug.h"

static void	handle_syntax_errors(t_node **tree, t_token *scanner, \
	t_list *var_list, int err);

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
	handle_syntax_errors(&node, scanner, var_list, err);
	return ((void *)node);
}

static void	handle_syntax_errors(t_node **tree, t_token *scanner, \
	t_list *var_list, int err)
{
	if (err != 0 || scanner)
	{
		if (err != 0)
			visit(NULL, *tree, check_syntax);
		else if (scanner)
			ft_dprintf(2, "%s%s\'\n", ERROR_MSG, scanner->wordl->word->value);
		while (scanner)
			tok_pop(&scanner);
		visit(NULL, *tree, drop);
		lst_set(var_list, SHELL, ECODE, SYNTAX_ERR);
		*tree = NULL;
	}
}
