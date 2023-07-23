/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:36:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/23 13:18:30 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "debug.h"
#include "minishell.h"
#include <libft.h>

int	execute(t_control *ctl, t_node *self)
{
	if (ctl->execute == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (self->type == SimpleCommandNode || self->type == CmdSuffixNode \
		|| self->type == CmdPrefixNode)
	{
		visit(ctl, self, expand);
		visit(ctl, self, preprocess);
	}
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
	else if (self->type == CmdPrefixNode)
		return (execute_prefix(ctl, self));
	else if (self->type == CmdSuffixNode)
		return (execute_suffix(ctl, self));
	else if (self->type == IORedirectNode)
		return (execute_io(ctl, self));
	return (EXIT_SUCCESS);
}
