/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:09:13 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 20:47:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "defines.h"
# include "list.h"

t_word	*word_new(char *str, int flags);

void	word_delete(t_word *word);

void	tok_push(t_token **tok_l, t_wordl *wordl, int type);
void	tok_pop(t_token **tok_l);
t_token	*tok_last(t_token *tok_l);

/* The lexical analysis function. */

t_token	*lex(char *str);
t_wordl	*get_next_token(char const *str, int *type);

t_wordl	*get_operator_token(char **s, int *flags, int *type);
t_wordl	*get_word(char **s, int *flags, int *type);

/* Wordlist API */
t_wordl	*wordl_new(t_word *word);
t_wordl	*wordl_last(t_wordl *wordl);

void	wordl_clear(t_wordl *wordl);
void	wordl_push_back(t_wordl **wordl, t_word *word);
void	wordl_push_front(t_wordl **wordl, t_word *word);

#endif