/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:27:03 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/29 21:33:03 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "debug.h"

static void	check_flag(t_tokl *tokens, t_wordl *word);

t_tokl	*lex(char *s)
{
	t_tokl	*tokens;
	t_wordl	*wordl;

	tokens = NULL;
	wordl = NULL;
	get_next_token(s);
	while (1)
	{
		wordl = get_next_token(NULL);
		if (!wordl)
			break ;
		check_flag(tokens, wordl);
		tok_push(&tokens, wordl);
	}
	print_tokens(tokens);
	return (tokens);
}

static void	check_flag(t_tokl *tokens, t_wordl *wordl)
{
	t_wordl	*tmp;

	if (wordl->word->flags & W_SUBSHELL_PIPE)
	{
		while (tokens)
		{
			tmp = tokens->wordl;
			while (tmp)
			{
				tmp->word->flags = tmp->word->flags | W_SUBSHELL_PIPE;
				tmp = tmp->next;
			}
			tokens = tokens->next;
		}
	}
}
