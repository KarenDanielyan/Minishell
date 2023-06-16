/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:01:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/16 22:51:09 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <libft.h>

static int	get_type(char *op);

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
 */
t_word	*get_operator_token(char **s, int *flags)
{
	t_word	*op_token;
	char	*tmp;
	char	*word;

	if (!s || !(*s) || !flags)
		return (NULL);
	ft_strappend(&word, **s);
	(*s)++;
	while (ft_strchr(OPERATORS, **s))
	{
		tmp = ft_strdup(word);
		ft_strappend(&tmp, **s);
		if (get_type(word) != NOTOP && get_type(tmp) == NOTOP)
			break ;
		free(tmp);
		ft_strappend(&word, **s);
		(*s)++;
	}
	if (tmp)
		free(tmp);
	op_token = word_new(word, get_type(word), *flags);
	return (op_token);
}

static int	get_type(char *op)
{
	if (ft_strlen(op) == 1 && *op == PIPE_OP)
		return (OP_PIPE);
	if (ft_strlen(op) == 1 && *op == ASSIGN_OP)
		return (VARASSIGN);
	if (ft_strlen(op) == 1 && *op == IN_OP)
		return (IO_FILE);
	if (ft_strlen(op) && *op == OUT_OP)
		return (IO_FILE);
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