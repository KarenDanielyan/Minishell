/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:25:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/08 15:36:21 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

void	drop(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self)
	{
		if (self->type == WordNode)
			wordl_clear(self->value.word);
		else if (self->type == ErrorNode)
			free(self->value.error);
		else if (self->type == CmdPrefixNode)
			node_list_clear(self->value.prefix, NULL);
		else if (self->type == CmdSuffixNode)
			node_list_clear(self->value.suffix, NULL);
		free(self);
	}
}
