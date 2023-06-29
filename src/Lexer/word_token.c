/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:57:19 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/29 22:05:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>

t_word	*get_param_word_token(char **s, int *flags);

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
	t_wordl	*word_token;
	char	*word;
	char	*follow;

	word_token = NULL;
	word = NULL;
	follow = NULL;
	if (s)
	{
		while (*s)
		{
			if (is_quote(**s, flags))
				wordl_push_back(&word_token, get_quote_token(s, flags));
			else if (**s == DOLLAR_SIGN)
				wordl_push_back(&word_token, get_param_word_token(s, flags));
			else if (ft_strchr(OPERATORS, **s) || (ft_iswhitespace(**s) && !(*flags & (W_SQUOTE | W_DQUOTE))))
				break ;
			else
			{
				
			}
		}
	}
	return (word_token);
}

t_word	*get_just_word_token(char **s, int *flags)
{
	char	*word;

	while (**s && !is_quote(**s, flags) && !ft_strchr(OPERATORS, **s)
		&& !(ft_iswhitespace(**s) && !(*flags & (W_SQUOTE | W_DQUOTE))))
	{
		ft_strappend(&word, **s);
		(*s)++;
	}
	return (word_new(word, WORD, (*flags | W_HASDOLLAR)));
}

	// if (**s == DOLLAR_SIGN && !word)
	// 	return (get_param_word_token(s, flags));
	// while (**s)
	// {
	// 	if (is_quote(**s, flags) || ft_strchr(OPERATORS, **s)
	// 		|| (ft_iswhitespace(**s) && !(*flags & (W_SQUOTE | W_DQUOTE))))
	// 		break ;
	// 	ft_strappend(&word, **s);
	// 	(*s)++;
	// }
	// word_token = word_new(word, WORD, *flags);

t_word	*get_param_word_token(char **s, int *flags)
{
	char	*word;
	char	*tmp;

	word = NULL;
	ft_strappend(&word, **s);
	tmp = ft_strdup(word);
	(*s)++;
	while (**s)
	{
		ft_strappend(&tmp, **s);
		if (!is_name(tmp))
			break ;
		ft_strappend(&word, **s);
		(*s)++;
	}
	free(tmp);
	return (word_new(word, WORD, (*flags | W_HASDOLLAR)));
}
