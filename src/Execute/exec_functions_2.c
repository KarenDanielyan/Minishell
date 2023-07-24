/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:01:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/24 15:57:06 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include <libft.h>
#include <stdio.h>

static void	set_child_fds(t_node *self);

void	execute_command(t_control *ctl, t_node *self)
{
	if (self->value.cmd.in_fd == FD_INIT)
		self->value.cmd.in_fd = STDIN_FILENO;
	if (self->value.cmd.out_fd == FD_INIT)
		self->value.cmd.out_fd = STDOUT_FILENO;
	if (self->value.cmd.command)
	{
		if (execute(ctl, self->value.cmd.prefix) == EXIT_FAILURE)
		{
			estat_set(ctl->estat, EXIT_FAILURE);
			return ;
		}
		set_child_fds(self);
		execute(ctl, self->value.cmd.command);
	}
}

void	execute_ccommand(t_control *ctl, t_node *self)
{
	int	pid;

	pid = my_fork(ctl);
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		dup2(self->value.c_cmd.in_fd, STDIN_FILENO);
		dup2(self->value.c_cmd.out_fd, STDOUT_FILENO);
		if (self->value.c_cmd.in_fd != STDIN_FILENO)
			close(self->value.c_cmd.in_fd);
		if (self->value.c_cmd.out_fd != STDOUT_FILENO)
			close(self->value.c_cmd.out_fd);
		execute(ctl, self->value.c_cmd.suffix);
		execute(ctl, self->value.c_cmd.list);
	}
	if (self->value.c_cmd.in_fd != STDIN_FILENO)
		close(self->value.c_cmd.in_fd);
	if (self->value.c_cmd.out_fd != STDOUT_FILENO)
		close(self->value.c_cmd.out_fd);
}

static void	set_child_fds(t_node *self)
{
	t_node	*cmd;

	cmd = self->value.cmd.command;
	if (cmd->type == CompoundCommandNode)
	{
		cmd->value.c_cmd.in_fd = self->value.cmd.in_fd;
		cmd->value.c_cmd.out_fd = self->value.cmd.out_fd;
	}
	else if (cmd->type == SimpleCommandNode)
	{
		cmd->value.s_cmd.in_fd = self->value.cmd.in_fd;
		cmd->value.s_cmd.out_fd = self->value.cmd.out_fd;
	}
}
