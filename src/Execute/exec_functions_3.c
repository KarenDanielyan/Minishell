/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:44:43 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/19 02:27:42 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <libft.h>
#include <stdio.h>

static t_flist	*get_builtin(t_control *ctl, t_node *word);
static void		exec(t_wordl *cmd, t_control *ctl);

void	execute_scommand(t_control *ctl, t_node *self)
{
	t_node	*cmd;
	t_flist	*builtin_cmd;
	int		pid;

	pid = 0;
	cmd = self->value.s_cmd.word;
	builtin_cmd = get_builtin(ctl, cmd);
	if (!builtin_cmd || \
		cmd->value.word->word->flags & (W_SUBSHELL_PAREN | W_SUBSHELL_PIPE))
		pid = fork();
	if (pid < 0)
	{
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execute(ctl, self->value.s_cmd.suffix);
		if (builtin_cmd)
			builtin_cmd->cmd(cmd->value.word, ctl);
		else
			exec(cmd->value.word, ctl);
	}
	else
	{
		if (self->value.s_cmd.in_fd != STDIN_FILENO)
			close(self->value.s_cmd.in_fd);
		if (self->value.s_cmd.out_fd != STDOUT_FILENO)
			close(self->value.s_cmd.out_fd);
	}
}


static t_flist	*get_builtin(t_control *ctl, t_node *word)
{
	char	*name;
	t_flist	*builtins;

	name = word->value.word->word->value;
	builtins = ctl->built_ins;
	while (builtins)
	{
		if (ft_strcmp(builtins->name, name) == 0)
			return (builtins);
		builtins = builtins->next;
	}
	return (builtins);
}

static void	exec(t_wordl *cmd, t_control *ctl)
{
	(void)cmd;
	(void)ctl;
}