/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:57:19 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/05 23:34:28 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "minishell.h"
#include <libft.h>

static t_word	*get_just_word(char **s, int *flags);
static t_word	*get_quoted_word(char **s, int *flags);

/**
 * @brief	Everything excepts quotes and operators are words.
 * 			Here we figure out what kind of words we have.
 * 			For example: $HELLO, cat etc.
 * 
 * @param s			The input string.
 * @param flags		Laws to be enforced while recognizign the token.
 * @return t_word*	Word token.
 */
t_wordl	*get_word(char **s, int *flags, int *type)
{
	t_wordl	*word_token;

	word_token = NULL;
	if (s)
	{
		while (*s)
		{
			if (ft_strchr(OPERATORS, **s) \
				|| (ft_iswhitespace(**s) && !(*flags & (W_SQUOTE | W_DQUOTE))))
				break ;
			else if (is_quote(**s, flags))
				wordl_push_back(&word_token, get_quoted_word(s, flags));
			else
				wordl_push_back(&word_token, get_just_word(s, flags));
		}
	}
	*type = WORD;
	return (word_token);
}

static t_word	*get_just_word(char **s, int *flags)
{
	char	*word;
	int		flag;
	t_word	*w;

	flag = *flags;
	word = NULL;
	while (**s && !is_quote(**s, flags) && !ft_strchr(OPERATORS, **s)
		&& !(ft_iswhitespace(**s) && !(*flags & (W_SQUOTE | W_DQUOTE))))
	{
		ft_strappend(&word, **s);
		if (**s == DOLLAR_SIGN)
			flag = flag | W_HASDOLLAR | W_PARMEXP;
		if (**s == TILDE)
			flag = flag | W_TILDEEXP;
		(*s)++;
	}
	w = word_new(word, flag);
	free(word);
	return (w);
}

static void	check_flag_change(char c, int *flags, int *flag)
{
	if (c == SQUOTE && is_quote(c, flags))
		*flags = *flags ^ W_SQUOTE;
	if (c == DQUOTE && is_quote(c, flags))
		*flags = *flags ^ W_DQUOTE;
	if (c == DOLLAR_SIGN)
		*flag = *flag | W_HASDOLLAR | W_PARMEXP;
	if (c == TILDE && !(*flag & (W_SQUOTE | W_DQUOTE)))
		*flag = *flag | W_TILDEEXP;
	if (c == EQUALS && !(*flag & (W_SQUOTE | W_DQUOTE)))
		*flag = *flag | W_ASSIGNMENT;
}

static t_word	*get_quoted_word(char **s, int *flags)
{
	char	*word;
	int		flag;
	t_word	*w;

	word = NULL;
	flag = 0;
	if (s && *s)
	{
		if (**s == SQUOTE)
			flag = flag | W_SQUOTE;
		if (**s == DQUOTE)
			flag = flag | W_DQUOTE;
		while (**s)
		{
			ft_strappend(&word, **s);
			check_flag_change(**s, flags, &flag);
			(*s)++;
			if (!ft_strchr(OPERATORS, **s) && !(flag & *flags))
				break ;
		}
		w = word_new(word, (*flags | flag));
		free(word);
		return (w);
	}
	return (NULL);
}
