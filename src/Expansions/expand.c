/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:55:38 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 16:06:13 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "parser.h"

void	set_assign(t_node *self);

void	expand(t_control *ctl, t_node *self)
{
	if (self->type == WordNode && !(self->value.word->word->flags & W_EXPAND))
	{
		tilde_exp(self, ctl->var_list);
		param_exp(self, ctl->var_list);
		field_splitting(self, ctl->var_list);
		join(self);
		glob_exp(self);
		set_assign(self);
		quote_removal(self);
		if (self->value.word)
		{
			self->value.word->word->flags = \
				self->value.word->word->flags | W_EXPAND;
		}
	}
	return ;
}

void	set_assign(t_node *self)
{
	t_wordl	*wordl;
	char	*c;
	char	quote_lvl;

	wordl = self->value.word;
	while (wordl)
	{
		c = wordl->word->value;
		quote_lvl = 0;
		while (*c)
		{
			if (*c == SQUOTE && quote_lvl != DQUOTE)
				quote_lvl = SQUOTE;
			if (*c == DQUOTE && quote_lvl != SQUOTE)
				quote_lvl = DQUOTE;
			if (*c == EQUALS)
				break ;
			c ++;
		}
		if (quote_lvl == 0 && *c == EQUALS)
			wordl->word->flags |= W_ASSIGNMENT;
		wordl = wordl->next;
	}
}
