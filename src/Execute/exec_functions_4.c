/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:53:34 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/19 17:13:31 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <libft.h>
#include <fcntl.h>

static void	execute_nodel(t_control *ctl, t_nodel *head);

void	execute_io(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self->value.io.type == IN || self->value.io.type == HERE)
	{
		if (self->value.io.type == IN)
			self->value.io.fd = open(self->value.io.filename, O_RDONLY);
		dup2(self->value.io.fd, STDIN_FILENO);
		close(self->value.io.fd);
	}
	else if (self->value.io.type == OUT || self->value.io.type == APPEND)
	{
		if (self->value.io.type == OUT)
			self->value.io.fd = open(self->value.io.filename, \
				O_CREAT | O_TRUNC | O_WRONLY, 0666);
		else
			self->value.io.fd = open(self->value.io.filename, \
				O_CREAT | O_APPEND | O_WRONLY, 0666);
		dup2(self->value.io.fd, STDOUT_FILENO);
		close(self->value.io.fd);
	}
}

void	execute_prefix(t_control *ctl, t_node *self)
{
	t_nodel	*prefix;

	prefix = self->value.prefix;
	execute_nodel(ctl, prefix);
}

void	execute_suffix(t_control *ctl, t_node *self)
{
	t_nodel	*suffix;

	suffix = self->value.suffix;
	execute_nodel(ctl, suffix);
}

static void	execute_nodel(t_control *ctl, t_nodel *head)
{
	while (head)
	{
		execute(ctl, head->node);
		head = head->next;
	}
}