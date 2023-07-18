/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:33:30 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/18 21:10:41 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

static void	remove_quotes(t_word *word);

void	quote_removal(t_node *self)
{
	t_wordl	*temp;

	temp = self->value.word;
	while (temp)
	{
		remove_quotes(temp->word);
		temp = temp->next;
	}
}

/**
 * @brief	remove_quotes() removes quotes from the word.
 * 
 */
static void	remove_quotes(t_word *word)
{
	char	*s;
	char	*unquoted_word;
	int		quote_lvl;

	unquoted_word = NULL;
	s = word->value;
	quote_lvl = 0;
	while (*s)
	{
		if (*s == DQUOTE && !(quote_lvl & W_SQUOTE))
			quote_lvl = quote_lvl ^ W_DQUOTE;
		else if (*s == SQUOTE && !(quote_lvl & W_DQUOTE))
			quote_lvl = quote_lvl ^ W_SQUOTE;
		else
			ft_strappend(&unquoted_word, *s);
		s++;
	}
	free(word->value);
	word->value = unquoted_word;
}
