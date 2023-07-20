/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:20:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 13:21:53 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <stdio.h>
#include <libft.h>
#include <ft_printf.h>
#include <fcntl.h>

static void	perform_redirect(t_control *ctl, t_node *self);
static int	is_valid_filename(t_wordl *word);

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
		perror(EPERROR);
		return (EXIT_FAILURE);
	}
	perform_redirect(ctl, self);
	return (EXIT_SUCCESS);
}

static void	perform_redirect(t_control *ctl, t_node *self)
{
	t_wordl	*filename;

	(void)ctl;
	filename = self->value.io.filename->value.word;
	if (self->value.io.type == IN || self->value.io.type == HERE)
	{
		if (self->value.io.type == IN)
			self->value.io.fd = open(filename->word->value, O_RDONLY);
		dup2(self->value.io.fd, STDIN_FILENO);
		close(self->value.io.fd);
	}
	else if (self->value.io.type == OUT || self->value.io.type == APPEND)
	{
		if (self->value.io.type == OUT)
			self->value.io.fd = open(filename->word->value, \
				O_CREAT | O_TRUNC | O_WRONLY, 0666);
		else
			self->value.io.fd = open(filename->word->value, \
				O_CREAT | O_APPEND | O_WRONLY, 0666);
		dup2(self->value.io.fd, STDOUT_FILENO);
		close(self->value.io.fd);
	}
}

static int	is_valid_filename(t_wordl *word)
{
	if (wordl_size(word) != 1)
		return (0);
	else
		return (1);
}
