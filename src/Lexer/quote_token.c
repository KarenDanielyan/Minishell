/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:02:26 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/22 19:23:16 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <libft.h>

t_word	*get_quote_token(char **s, int *flags)
{
	t_word	*quote_token;

	quote_token = NULL;
	if (**s == '\'')
	{
		if (*flags ^ W_SQUOTE)
			quote_token = word_new(ft_substr(*s, 0, 1), SQUOTE_OPEN, *flags);
		else
			quote_token = word_new(ft_substr(*s, 0, 1), SQUOTE_CLOSE, *flags);
		*flags = *flags ^ W_SQUOTE;
	}
	if (**s == '\"')
	{
		if (*flags ^ W_DQUOTE)
			quote_token = word_new(ft_substr(*s, 0, 1), DQUOTE_OPEN, *flags);
		else if (*flags & W_DQUOTE)
			quote_token = word_new(ft_substr(*s, 0, 1), DQUOTE_CLOSE, *flags);
		*flags = *flags ^ W_DQUOTE;
	}
	(*s)++;
	return (quote_token);
}
