/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:33:30 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/26 20:36:40 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <stdio.h>

static void	get_dimensions(char *word, char **from, char **to);

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
void	remove_quotes(t_word *word)
{
	char	*s;
	char	*from;
	char	*to;
	char	*unquoted_word;

	s = word->value;
	from = NULL;
	to = NULL;
	unquoted_word = NULL;
	get_dimensions(s, &from, &to);
	if (!(word->flags & (W_SQUOTE | W_DQUOTE)) || !from || !to || (from == to))
		return ;
	while (s != from)
		ft_strappend(&unquoted_word, *s++);
	s ++;
	while (s != to)
		ft_strappend(&unquoted_word, *s++);
	s ++;
	while (*s)
		ft_strappend(&unquoted_word, *s++);
	free(word->value);
	word->value = unquoted_word;
}

static void	get_dimensions(char *word, char **from, char **to)
{
	char	*s;

	s = word;
	while (*s)
	{
		if (*s == SQUOTE || *s == DQUOTE)
			break ;
		s ++;
	}
	if (*s != 0)
	{
		*from = s;
		*to = ft_strrchr(word, *s);
	}
}
