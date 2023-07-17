/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:55:38 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/17 19:29:14 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "parser.h"

void	expand(t_control *ctl, t_node *self)
{
	if (self->type == WordNode)
	{
		tilde_exp(self, ctl->var_list);
		param_exp(self, ctl->var_list);
		field_splitting(self, ctl->var_list);
		join(self);
		//glob_exp(self);
		quote_removal(self);
	}
	return ;
}
