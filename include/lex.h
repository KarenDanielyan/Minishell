/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:09:13 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/25 19:25:26 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "defines.h"
# include "list.h"

void	tok_push(t_token **tok_l, t_wordl *wordl, int type);
void	tok_pop(t_token **tok_l);
t_token	*tok_last(t_token *tok_l);

/* Token Checker */
int		check_tokens(t_token *scanner);

/* The lexical analysis function. */

t_token	*lex(t_control *ctl);
t_wordl	*get_next_token(char const *str, int *type);

t_wordl	*get_operator_token(char **s, int *flags, int *type);
t_wordl	*get_word(char **s, int *flags, int *type);

#endif
