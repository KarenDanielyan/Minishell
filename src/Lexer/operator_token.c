/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:47:54 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/05 23:38:15 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "list.h"
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
 * 	'(' and ')'
 */
t_wordl	*get_operator_token(char **s, int *flags, int *type)
{
	t_wordl	*op_wordl;
	char	*tmp;
	char	*word;

	word = NULL;
	tmp = NULL;
	if (!s || !(*s) || !flags)
		return (NULL);
	while (**s && ft_strchr(OPERATORS, **s))
	{
		ft_strappend(&tmp, **s);
		if (word && get_type(word) != UNKNOWN && get_type(tmp) == UNKNOWN)
			break ;
		ft_strappend(&word, **s);
		(*s)++;
	}
	free(tmp);
	op_wordl = wordl_new(word_new(word, *flags));
	*type = get_type(word);
	check_flags_change(flags, *type);
	free(word);
	return (op_wordl);
}

static int	get_type(char *op)
{
	int	len;

	len = ft_strlen(op);
	if (len == 1 && *op == PIPE_OP)
		return (OP_PIPE);
	if (len == 1 && (*op == LESS || *op == GREAT))
		return (IO_FILE);
	if (len == 1 && *op == LPAREN)
		return (SUBSHELL_OPEN);
	if (len == 1 && *op == RPAREN)
		return (SUBSHELL_CLOSE);
	if (ft_strcmp(op, AND_IF) == 0)
		return (AND_OP);
	if (ft_strcmp(op, OR_IF) == 0)
		return (OR_OP);
	if (ft_strcmp(op, DGREAT) == 0)
		return (IO_APPEND);
	if (ft_strcmp(op, DLESS) == 0)
		return (IO_HERE);
	return (UNKNOWN);
}

static void	check_flags_change(int *flags, int token_type)
{
	static int	subshell_depth;

	if (token_type == SUBSHELL_OPEN)
	{
		*flags = *flags | W_SUBSHELL_PAREN;
		subshell_depth ++;
	}
	if (token_type == SUBSHELL_CLOSE)
	{
		subshell_depth --;
		if (subshell_depth == 0)
			*flags = *flags ^ W_SUBSHELL_PAREN;
		if (*flags & W_SUBSHELL_PIPE)
			*flags = *flags ^ W_SUBSHELL_PIPE;
	}
	if (token_type == OP_PIPE)
		*flags = *flags | W_SUBSHELL_PIPE;
	if ((token_type == AND_OP || token_type == OR_OP)
		&& (*flags & W_SUBSHELL_PIPE))
		*flags = *flags ^ W_SUBSHELL_PIPE;
}
