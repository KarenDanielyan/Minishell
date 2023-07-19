/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:36:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/19 15:06:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include <libft.h>

void	execute(t_control *ctl, t_node *self)
{
	if (self->type == ListNode)
		execute_list(ctl, self);
	else if (self->type == PipelineNode)
		execute_pipeline(ctl, self);
	else if (self->type == CommandNode)
		execute_command(ctl, self);
	else if (self->type == SimpleCommandNode)
		execute_scommand(ctl, self);
	else if (self->type == CompoundCommandNode)
		execute_ccommand(ctl, self);
	// else if (self->type == CmdPrefixNode)
	// 	execute_prefix(ctl, self);
	// else if (self->type == CmdSuffixNode)
	// 	execute_suffix(ctl, self);
	// else if (self->type == IORedirectNode)
	// 	execute_io(ctl, self);
}
