/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:17:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/15 19:12:16 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "list.h"
#include <libft.h>

int		is_whitespace(char c);
t_word	*get_quote_token(char **s, int *flags);
t_word	*get_operator_token(char **s, int *flags);
t_word	*get_word(char **s, int *flags);

/**
 * @brief		Get the next token object
 * 
 * @param str	Is the string that has to be parsed.
 * 				On the subsequent calls, you pass NULL as the argument,
 * 				until you reach the end of the string.
 * @return t_word*	Returns the next token object found in the string.
 * 			NOTE:	Function will return NULL, when either string has ended,
 * 					or there are no more tokens to get from the string.
 */
t_word	*get_next_token(char const *str)
{
	static char	*s;
	static int	flags;
	t_word		*token;

	if (!s)
		s = (char *)str;
	token = NULL;
	while (s)	// Magic happens here
	{
		while (is_whitespace(*s))
			s ++;
		if (ft_strchr(QUOTES, *s) && (flags ^ (W_SQUOTED | W_DQUOTED)))
			token = get_quote_token(&s, &flags);
		if (ft_strchr(OPERATORS, *s) && token == NULL)
			token = get_operator_token(&s, &flags);
		if (token == NULL)
			token = get_word(&s, &flags);
	}
	return (NULL);
}

t_word	*get_operator_token(char **s, int *flags)
{
	t_word	*op_token;

	op_token = NULL;
	if (ft_strncmp(*s, AND_LIST, 2) == 0)
		return (NULL);
	if (ft_strncmp(*s, OR_LIST, 2) == 0)
		return (NULL);
	if (ft_strncmp(*s, IO_HERE, 2) == 0)
		return (NULL);
	if (ft_strncmp(*s, IO_APPEND, 2) == 0)
		return (NULL);
	if (*s == PIPE_OP)
		return (NULL);
	if (*s == IN_OP)
		return (NULL);
	return (op_token);
}

t_word	*get_quote_token(char **s, int *flags)
{
	t_word	quote_token;

	quote_token = NULL;
	if (*s == '\'')
	{
		if (*flags ^ W_SQUOTED)
			quote_token = word_new(ft_substr(*s, 0, 1), SQUOTE_OPEN);
		else
			quote_token = word_new(ft_substr(*s, 0, 1), SQUOTE_CLOSE);
		*flags = *flags ^ W_SQUOTED;
	}
	if (*s == '\"')
	{
		if (*flafs ^ W_DQUOTED)
			quote_token = word_new(ft_substr(*s, 0, 1), DQUOTE_OPEN);
		else if (*flags & W_DQUOTED)
			quote_token = word_new(ft_substr(*s, 0, 1), SQUOTE_CLOSE);
		*flags = *flags ^ W_DQUOTED;
	}
	*s++;
	return (quote_token);
}

int	is_whitespace(char c)
{
	if (ft_strchr(" \t\n\v", c))
		return (1);
	return (0);
}
