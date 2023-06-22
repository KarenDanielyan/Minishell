/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:27:03 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/22 14:50:44 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "debug.h"

static void	check_flag(t_tokl *tokens, t_word *word);

t_tokl	*lex(char *s)
{
	t_tokl	*tokens;
	t_word	*word;

	tokens = NULL;
	word = NULL;
	get_next_token(s);
	while (1)
	{
		word = get_next_token(NULL);
		if (!word)
			break ;
		check_flag(tokens, word);
		tok_push(&tokens, word);
	}
	print_tokens(tokens);
	return (tokens);
}

static void	check_flag(t_tokl *tokens, t_word *word)
{
	if (word->flags & W_SUBSHELL_PIPE)
	{
		while (tokens)
		{
			tokens->word->flags = tokens->word->flags | W_SUBSHELL_PIPE;
			tokens = tokens->next;
		}
	}
}
