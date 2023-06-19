/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:57:19 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/19 15:49:50 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <libft.h>
#include <stdio.h>

/**
 * @brief	Everything excepts quotes and operators are words.
 * 			Here we figure out what kind of words we have.
 * 			For example: $HELLO, cat etc.
 * 
 * @param s			The input string.
 * @param flags		Laws to be enforced while recognizign the token.
 * @return t_word*	Word token.
 */
t_word	*get_word(char **s, int *flags)
{
	t_word	*word_token;
	char	*word;

	word_token = NULL;
	word = NULL;
	if (s)
	{
		while (*s && !ft_strchr(OPERATORS, **s) && !ft_strchr(QUOTES, **s) \
				&& !ft_iswhitespace(**s))
		{
			ft_strappend(&word, **s);
			(*s)++;
		}
		word_token = word_new(word, WORD, *flags);
	}
	return (word_token);
}
