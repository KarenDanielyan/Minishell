/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:43:01 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/30 16:46:08 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>
#include <stdio.h>

t_word	*word_new(char *str, int flags)
{
	t_word	*word;

	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	word->value = str;
	word->flags = flags;
	return (word);
}

void	word_delete(t_word *word)
{
	free(word->value);
	free(word);
}

t_token	*tok_last(t_token *tok_l)
{
	if (tok_l)
	{
		while (tok_l->next)
			tok_l = tok_l->next;
	}
	return (tok_l);
}

void	tok_push(t_token **tok_l, t_wordl *wordl, int type)
{
	t_token	*token;

	if (tok_l)
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->type = type;
		token->prev = NULL;
		token->next = NULL;
		token->wordl = wordl;
		if (*tok_l)
		{
			token->prev = tok_last(*tok_l);
			tok_last(*tok_l)->next = token;
		}
		else
			*tok_l = token;
	}
}

void	tok_pop(t_token **tok_l)
{
	t_token	*last;

	if (tok_l && *tok_l)
	{
		last = tok_last(*tok_l);
		wordl_clear(last->wordl);
		last->prev->next = NULL;
		free(last);
	}
}
