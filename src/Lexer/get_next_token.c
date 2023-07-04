/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:17:27 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 21:12:54 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "list.h"
#include <libft.h>

static t_wordl	*gnt_init(char **s, const char *str);
static t_wordl	*gnt_cleanup(char **s, int *flags);

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
t_wordl	*get_next_token(char const *str, int *type)
{
	static char	*s;
	static int	flags;

	if (!s)
		return (gnt_init(&s, str));
	if (s && *s)
	{
		while (*s && ft_iswhitespace(*s))
			s++;
		if (*s && ft_strchr(OPERATORS, *s))
			return (get_operator_token(&s, &flags, type));
		if (*s)
			return (get_word(&s, &flags, type));
	}
	return (gnt_cleanup(&s, &flags));
}

static t_wordl	*gnt_init(char **s, const char *str)
{
	*s = (char *)str;
	return (NULL);
}

static t_wordl	*gnt_cleanup(char **s, int *flags)
{
	*s = NULL;
	*flags = 0;
	return (NULL);
}
