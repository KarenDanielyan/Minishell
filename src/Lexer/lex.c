/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:27:03 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/19 15:41:13 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "debug.h"

t_tokl	*lex(char *s)
{
	t_tokl	*tokens;
	t_word	*word;

	tokens = NULL;
	word = NULL;
	while (1)
	{
		word = get_next_token(s);
		if(word == NULL)
			break ;
		tok_push(&tokens, word);
	}
	print_tokens(tokens);
	return (tokens);
}
