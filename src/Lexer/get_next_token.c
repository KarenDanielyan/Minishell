/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:17:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/15 14:47:59 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "list.h"
#include <libft.h>

int	is_whitespace(char c);

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

	if (!s)
		s = (char *)str;
	while (s)	// Magic happens here;
	{
		while (is_whitespace(*s))
			s ++;
		if (ft_strchr(QUOTES, *s))
			return (get_quote_token(&s, &flags));
		if (ft_strchr(OPERATORS, *s))
			return (get_operator_token(&s, &flags));
		return (get_word(&s, &flags));
	}
	return (NULL);
}

int	is_whitespace(char c)
{
	if (ft_strchr(" \t\n\v", c))
		return (1);
	return (0);
}
