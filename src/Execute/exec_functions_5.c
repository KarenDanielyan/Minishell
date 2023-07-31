/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:20:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/31 18:55:10 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>
#include <ft_printf.h>
#include <fcntl.h>

static int	perform_redirect(t_control *ctl, t_node *self);
static int	is_valid_filename(t_wordl *word);
static int	perform_out(t_node *self);
static int	perform_in(t_node *self);

int	execute_io(t_control *ctl, t_node *self)
{
	t_wordl	*filename;

	(void)ctl;
	filename = self->value.io.filename->value.word;
	if (!is_valid_filename(filename))
	{
		ft_dprintf(STDERR_FILENO, ERROR_IO);
		return (EXIT_FAILURE);
	}
	if (access(filename->word->value, F_OK) < 0 && self->value.io.type == IN)
	{
		ft_dprintf(STDERR_FILENO, "%s%s: %s\n", EPERROR, \
			filename->word->value, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (perform_redirect(ctl, self));
}

static int	perform_redirect(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self->value.io.type == IN || self->value.io.type == HERE)
		return (perform_in(self));
	else if (self->value.io.type == OUT || self->value.io.type == APPEND)
		return (perform_out(self));
	return (EXIT_SUCCESS);
}

static int	perform_in(t_node *self)
{
	t_wordl	*filename;

	filename = self->value.io.filename->value.word;
	if (self->value.io.type == IN)
		self->value.io.fd = open(filename->word->value, O_RDONLY);
	if (dup2(self->value.io.fd, STDIN_FILENO))
	{
		ft_dprintf(STDERR_FILENO, "%s%s\n", EPERROR, strerror(errno));
		return (EXIT_FAILURE);
	}
	close(self->value.io.fd);
	return (EXIT_SUCCESS);
}

static int	perform_out(t_node *self)
{
	t_wordl	*filename;

	filename = self->value.io.filename->value.word;
	if (self->value.io.type == OUT)
		self->value.io.fd = open(filename->word->value, \
			O_CREAT | O_TRUNC | O_WRONLY, 0666);
	else
		self->value.io.fd = open(filename->word->value, \
			O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (self->value.io.fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s%s: %s\n", EPERROR, \
			filename->word->value, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(self->value.io.fd, STDOUT_FILENO) < 0)
	{
		ft_dprintf(STDERR_FILENO, "%s%s\n", EPERROR, strerror(errno));
		return (EXIT_FAILURE);
	}
	close(self->value.io.fd);
	return (EXIT_SUCCESS);
}

static int	is_valid_filename(t_wordl *word)
{
	if (wordl_size(word) != 1)
		return (0);
	else
		return (1);
}
