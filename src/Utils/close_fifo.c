/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fifo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:39:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 14:33:51 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"

void	close_fifo(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self->type == PipelineNode)
	{
		close(self->value.pipeline.pip.in);
		close(self->value.pipeline.pip.out);
	}
}
