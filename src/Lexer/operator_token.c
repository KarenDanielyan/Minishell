/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:01:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/20 17:21:26 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <libft.h>

static int	get_type(char *op);
static void	check_flags_change(int *flags, int token_type);

/**
 * @brief	Get the operator token.
 * 
 * 	List of operators:
 * 	|
 * 	&&
 * 	||
 * 	>> or >
 * 	<< or <
 * 	=
 * 	'(' and ')'
 */
t_word	*get_operator_token(char **s, int *flags)
{
	t_word	*op_token;
	char	*tmp;
	char	*word;

	word = NULL;
	tmp = NULL;
	if (!s || !(*s) || !flags)
		return (NULL);
	while (ft_strchr(OPERATORS, **s))
	{
		ft_strappend(&tmp, **s);
		if (word && get_type(word) != NOTOP && get_type(tmp) == NOTOP)
			break ;
		ft_strappend(&word, **s);
		(*s)++;
	}
	free(tmp);
	op_token = word_new(word, get_type(word), *flags);
	check_flags_change(flags, get_type(word));
	return (op_token);
}

static int	get_type(char *op)
{
	int	len;

	len = ft_strlen(op);
	if (len == 1 && *op == PIPE_OP)
		return (OP_PIPE);
	if (len == 1 && *op == ASSIGN_OP)
		return (VARASSIGN);
	if (len == 1 && *op == IN_OP)
		return (IO_FILE);
	if (len == 1 && *op == OUT_OP)
		return (IO_FILE);
	if (len == 1 && *op == SUBSHELL_OPEN)
		return (LEFT_PAREN);
	if (len == 1 && *op == SUBSHELL_CLOSE)
		return (RIGHT_PAREN);
	if (ft_strcmp(op, AND_LIST) == 0)
		return (AND_IF);
	if (ft_strcmp(op, OR_LIST) == 0)
		return (OR_IF);
	if (ft_strcmp(op, APPEND_OP) == 0)
		return (IO_APPEND);
	if (ft_strcmp(op, HEREDOC_OP) == 0)
		return (IO_HERE);
	return (NOTOP);
}

static void	check_flags_change(int *flags, int token_type)
{
	if (token_type == LEFT_PAREN)
		*flags = *flags | W_SUBSHELL_PAREN;
	if (token_type == RIGHT_PAREN)
		*flags = *flags ^ W_SUBSHELL_PAREN;
	if (token_type == OP_PIPE)
		*flags = *flags | W_SUBSHELL_PIPE;
	if (token_type == AND_IF && (*flags & W_SUBSHELL_PIPE))
		*flags = *flags ^ W_SUBSHELL_PIPE;
}
