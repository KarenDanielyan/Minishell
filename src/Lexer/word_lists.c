/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:43:01 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/19 16:18:14 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>
#include <stdio.h>

t_word	*word_new(char *str, int type, int flags)
{
	t_word	*word;

	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	word->value = str;
	word->type = type;
	word->flags = flags;
	return (word);
}

void	word_delete(t_word *word)
{
	free(word->value);
	free(word);
}

t_tokl	*tok_last(t_tokl *tok_l)
{
	if (tok_l)
	{
		while (tok_l->next)
			tok_l = tok_l->next;
	}
	return (tok_l);
}

void	tok_push(t_tokl **tok_l, t_word *word)
{
	t_tokl	*token;

	token = (t_tokl *)malloc(sizeof(t_tokl));
	token->prev = NULL;
	token->next = NULL;
	token->word = word;
	if (tok_l && *tok_l)
	{
		token->prev = *tok_l;
		tok_last(*tok_l)->next = token;
	}
	else
		*tok_l = token;
}

void	tok_pop(t_tokl **tok_l)
{
	t_tokl	*last;

	if (tok_l && *tok_l)
	{
		last = tok_last(*tok_l);
		word_delete(last->word);
		last->prev->next = NULL;
		free(last);
	}
}
