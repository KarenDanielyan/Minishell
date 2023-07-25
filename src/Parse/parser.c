/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:00:54 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/25 23:24:12 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"
#include "parser.h"
#include "debug.h"

static void	handle_syntax_errors(t_node **tree, t_token *scanner, \
	t_control *ctl, int err);

/**
 * @brief	parse() consumes the sequence of tokens and returns
 * 			an abstract syntax tree on successfull parsing.
 * 
 * 			If parsing encounters an error, it wil set the err flag as 1,
 * 			indicating that syntax error was encountered during parsing.
*/
t_node	*parse(t_token *scanner, t_control *ctl)
{
	t_node	*node;
	int		err;

	err = 0;
	if (scanner == NULL)
		return (NULL);
	node = parse_list(ctl, &scanner, &err);
	handle_syntax_errors(&node, scanner, ctl, err);
	return ((void *)node);
}

static void	handle_syntax_errors(t_node **tree, t_token *scanner, \
	t_control *ctl, int err)
{
	if (err != 0 || scanner)
	{
		if (err != 0)
			visit(NULL, *tree, check_syntax);
		else if (scanner)
			ft_dprintf(STDERR_FILENO, "%s%s\'\n", ERROR_MSG, \
				scanner->wordl->word->value);
		while (scanner)
			tok_pop(&scanner);
		visit(NULL, *tree, drop);
		if (WIFEXITED(*(ctl->estat)))
			estat_set(ctl->estat, SYNTAX_ERR);
		*tree = NULL;
	}
}
