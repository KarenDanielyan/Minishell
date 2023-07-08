/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:55:38 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/08 15:49:18 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "parser.h"

void	expand(t_control *ctl, t_node *self)
{
	if (self->type == WordNode)
	{
		tilde_expand(self);
		param_expand(self);
		field_splitting(self, ctl->var_list);
		glob_expand(self);
		quote_removal(self);
	}
	return ;
}
