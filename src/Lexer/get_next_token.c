/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:17:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/22 14:32:12 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "list.h"
#include <libft.h>
#include <stdio.h>

static t_word	*gnt_init(char **s, const char *str);
static void		gnt_cleanup(char **s, int *flags);

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
		gnt_init(&s, str);
	token = NULL;
	if (s && *s)
	{
		while (*s && ft_iswhitespace(*s))
			s++;
		if (*s && ft_strchr(QUOTES, *s) && (flags ^ (W_SQUOTE | W_DQUOTE)))
			token = get_quote_token(&s, &flags);
		if (*s && ft_strchr(OPERATORS, *s) && token == NULL)
			token = get_operator_token(&s, &flags);
		if (*s && token == NULL)
			token = get_word(&s, &flags);
	}
	else
		gnt_cleanup(&s, &flags);
	return (token);
}

static t_word	*gnt_init(char **s, const char *str)
{
	*s = (char *)str;
	return (NULL);
}


static void gnt_cleanup(char **s, int *flags)
{
	*s = NULL;
	*flags = 0;
}
