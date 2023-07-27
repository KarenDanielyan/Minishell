/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:50:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/27 13:54:55 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include <libft.h>
#include <stdio.h>

static void	set_fd_helper(t_node *child, int fd, int fd_type);
static void	set_fd_values(t_node *self);

void	execute_list(t_control *ctl, t_node *self)
{
	execute(ctl, self->value.list.left);
	while (wait(ctl->estat) != -1)
		;
	dup2(ctl->in_dup, STDIN_FILENO);
	dup2(ctl->out_dup, STDOUT_FILENO);
	if (*(ctl->estat) == 0 && self->value.list.type == AND)
		execute(ctl, self->value.list.right);
	else if (*(ctl->estat) != 0 && self->value.list.type == OR)
		execute(ctl, self->value.list.right);
}

void	execute_pipeline(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self->value.pipeline.in_fd == FD_INIT)
		self->value.pipeline.in_fd = STDIN_FILENO;
	if (self->value.pipeline.out_fd == FD_INIT)
		self->value.pipeline.out_fd = STDOUT_FILENO;
	set_fd_values(self);
	execute(ctl, self->value.pipeline.left);
	execute(ctl, self->value.pipeline.right);
}

static void	set_fd_values(t_node *self)
{
	t_node	*left;
	t_node	*right;
	int		pip[2];

	if (pipe(pip) < 0)
	{
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	left = self->value.pipeline.left;
	right = self->value.pipeline.right;
	self->value.pipeline.pip.in = pip[0];
	self->value.pipeline.pip.out = pip[1];
	set_fd_helper(left, self->value.pipeline.in_fd, IN);
	set_fd_helper(left, pip[1], OUT);
	set_fd_helper(right, pip[0], IN);
	set_fd_helper(right, self->value.pipeline.out_fd, OUT);
}

static void	set_fd_helper(t_node *child, int fd, int fd_type)
{
	if (fd_type == IN)
	{
		if (child->type == PipelineNode)
			child->value.pipeline.in_fd = fd;
		else if (child->type == CommandNode)
			child->value.cmd.in_fd = fd;
		else if (child->type == SimpleCommandNode)
			child->value.s_cmd.in_fd = fd;
		else if (child->type == CompoundCommandNode)
			child->value.c_cmd.in_fd = fd;
	}
	else
	{
		if (child->type == PipelineNode)
			child->value.pipeline.out_fd = fd;
		else if (child->type == CommandNode)
			child->value.cmd.out_fd = fd;
		else if (child->type == SimpleCommandNode)
			child->value.s_cmd.out_fd = fd;
		else if (child->type == CompoundCommandNode)
			child->value.c_cmd.out_fd = fd;
	}
}
