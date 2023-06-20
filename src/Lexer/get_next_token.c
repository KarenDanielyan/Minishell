/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:17:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/19 18:26:12 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "list.h"
#include <libft.h>

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
	if (s && *s)
	{
		while (ft_iswhitespace(*s))
			s ++;
		if (ft_strchr(QUOTES, *s) && (flags ^ (W_SQUOTE | W_DQUOTE)))
			token = get_quote_token(&s, &flags);
		if (ft_strchr(OPERATORS, *s) && token == NULL)
			token = get_operator_token(&s, &flags);
		if (token == NULL)
			token = get_word(&s, &flags);
	}
	return (token);
}
