/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:33:30 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/31 12:13:29 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <stdio.h>

void	quote_removal(t_node *self)
{
	t_wordl	*temp;

	temp = self->value.word;
	while (temp)
	{
		remove_quotes(temp->word);
		if (temp->word->value == NULL)
		{
			ft_strappend(&(temp->word->value), 0);
			temp->word->flags = W_HASQUOTEDNULL;
		}
		temp = temp->next;
	}
}

void	remove_quotes(t_word *word)
{
	char	*s;
	char	*unquoted_word;
	int		quote_lvl;

	unquoted_word = NULL;
	s = word->value;
	quote_lvl = 0;
	if (!(word->flags & (W_SQUOTE | W_DQUOTE)))
		return ;
	while (*s)
	{
		if ((*s == SQUOTE || *s == DQUOTE) \
			&& (quote_lvl == 0 || *s == quote_lvl))
			quote_lvl ^= *s;
		else
		{
			if (*s == 1)
				s++;
			ft_strappend(&unquoted_word, *s);
		}
		s ++;
	}
	free(word->value);
	word->value = unquoted_word;
}
