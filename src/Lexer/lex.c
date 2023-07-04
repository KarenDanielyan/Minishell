/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:27:03 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 21:13:27 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "debug.h"
#include "minishell.h"

static void	check_flag(t_token *tokens, t_wordl *word);

t_token	*lex(char *s)
{
	t_token	*tokens;
	t_wordl	*wordl;
	int		type;

	tokens = NULL;
	wordl = NULL;
	get_next_token(s, NULL);
	while (1)
	{
		wordl = get_next_token(NULL, &type);
		if (!wordl)
			break ;
		check_flag(tokens, wordl);
		tok_push(&tokens, wordl, type);
	}
	return (tokens);
}

static void	check_flag(t_token *tokens, t_wordl *wordl)
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
