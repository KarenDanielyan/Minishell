/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:01:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/30 18:16:52 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include <libft.h>
#include <stdio.h>

static void	set_ecode_and_exit(t_control *ctl);
static void	set_child_fds(t_node *self);

void	execute_command(t_control *ctl, t_node *self)
{
	if (self->value.cmd.in_fd == FD_INIT)
		self->value.cmd.in_fd = STDIN_FILENO;
	if (self->value.cmd.out_fd == FD_INIT)
		self->value.cmd.out_fd = STDOUT_FILENO;
	if (execute(ctl, self->value.cmd.prefix) == EXIT_FAILURE)
	{
		estat_set(ctl->estat, EXIT_FAILURE);
		return ;
	}
	if (self->value.cmd.command)
	{
		set_child_fds(self);
		execute(ctl, self->value.cmd.command);
	}
}

void	execute_ccommand(t_control *ctl, t_node *self)
{
	ctl->cur_pid = my_fork(ctl);
	if (ctl->cur_pid < 0)
		return ;
	if (ctl->cur_pid == 0)
	{
		dup2(self->value.c_cmd.in_fd, STDIN_FILENO);
		dup2(self->value.c_cmd.out_fd, STDOUT_FILENO);
		if (self->value.c_cmd.in_fd != STDIN_FILENO)
			close(self->value.c_cmd.in_fd);
		if (self->value.c_cmd.out_fd != STDOUT_FILENO)
			close(self->value.c_cmd.out_fd);
		if (execute(ctl, self->value.c_cmd.suffix) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		execute(ctl, self->value.c_cmd.list);
		set_ecode_and_exit(ctl);
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

static void	set_ecode_and_exit(t_control *ctl)
{
	while (wait(ctl->estat) != -1)
		;
	if (WIFEXITED(*(ctl->estat)))
		exit(WEXITSTATUS(*(ctl->estat)));
	else
		exit(WTERMSIG(*(ctl->estat)));
}
