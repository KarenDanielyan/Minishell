/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:33:30 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/27 15:43:45 by kdaniely         ###   ########.fr       */
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

// /**
//  * @brief	remove_quotes() removes quotes from the word.
//  * 
//  */
// void	remove_quotes(t_word *word)
// {
// 	char	*s;
// 	char	*from;
// 	char	*to;
// 	char	*unquoted_word;

// 	s = word->value;
// 	from = NULL;
// 	to = NULL;
// 	unquoted_word = NULL;
// 	get_dimensions(s, &from, &to);
// 	if (!(word->flags & (W_SQUOTE | W_DQUOTE)) || !from || !to || (from == to))
// 		return ;
// 	while (s != from)
// 		ft_strappend(&unquoted_word, *s++);
// 	s ++;
// 	while (s != to)
// 		ft_strappend(&unquoted_word, *s++);
// 	s ++;
// 	while (*s)
// 		ft_strappend(&unquoted_word, *s++);
// 	free(word->value);
// 	word->value = unquoted_word;
// }

// static void	get_dimensions(char *word, char **from, char **to)
// {
// 	char	*s;

// 	s = word;
// 	while (*s)
// 	{
// 		if (*s == SQUOTE || *s == DQUOTE)
// 			break ;
// 		s ++;
// 	}
// 	if (*s != 0)
// 	{
// 		*from = s;
// 		*to = ft_strrchr(word, *s);
// 	}
// }

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
