/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:09:13 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/14 14:22:41 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "defines.h"
# include "list.h"

/**
 * @brief	Atomic entity of our lexical analysis
 * 
 * @param token_type	What type of word is this? (ex. command io_here, etc.)
 * @param flags			Flags for the word (refer to defines.h so see possible values).
 * @param value			The word itself (ex. ">", "<<", "cat")
 */
typedef struct s_word
{
	int		type;
	int		flags;
	char	*value;
}	t_word;

/**
 * @brief	Wordlist.
 */
typedef struct s_wordl
{
	struct s_word	*word;
	struct s_wordl	*next;
}	t_wordl;

/**
 * @brief	Generated tokens list. Lexer will return this
 * 			after tokenizing the input.
 */
typedef struct s_tokl
{
	struct s_word	*word;
	struct s_tokl	*prev;
	struct s_tokl	*next;
}	t_tokl;

t_word	*word_new(char *str, int type, int flags);

void	tok_push(t_tokl **tok_l, t_word *word);
void	tok_pop(t_tokl **tok_l);
t_tokl	*tok_last(t_tokl *tok_l);


/* The lexical analysis function. */
t_word	*get_next_token(char const *str, t_list *var_list);

#endif