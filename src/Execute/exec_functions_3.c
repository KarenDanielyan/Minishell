/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:44:43 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/19 15:06:09 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include <libft.h>
#include <stdio.h>

static t_flist	*get_builtin(t_control *ctl, t_node *word);
static void		handle_fork(int pid, t_node *self, \
	t_flist *builtin_cmd, t_control *ctl);
static void		exec(t_wordl *cmd, t_control *ctl);

void	execute_scommand(t_control *ctl, t_node *self)
{
	t_flist	*builtin_cmd;
	t_node	*word;
	int		pid;

	pid = 0;
	word = self->value.s_cmd.word;
	builtin_cmd = get_builtin(ctl, word);
	if (!builtin_cmd || \
		word->value.word->word->flags & (W_SUBSHELL_PAREN | W_SUBSHELL_PIPE))
		pid = fork();
	if (pid < 0)
	{
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	handle_fork(pid, self, builtin_cmd, ctl);
}

static void	handle_fork(int pid, t_node *self, \
	t_flist *builtin_cmd, t_control *ctl)
{
	t_node	*cmd;

	cmd = self->value.s_cmd.word;
	if (pid == 0)
	{
		dup2(self->value.s_cmd.in_fd, STDIN_FILENO);
		dup2(self->value.s_cmd.out_fd, STDOUT_FILENO);
	}
	if (self->value.s_cmd.in_fd != STDIN_FILENO)
		close(self->value.s_cmd.in_fd);
	if (self->value.s_cmd.out_fd != STDOUT_FILENO)
		close(self->value.s_cmd.out_fd);
	if (pid == 0)
	{
		execute(ctl, self->value.s_cmd.suffix);
		if (builtin_cmd)
			builtin_cmd->cmd(cmd->value.word, ctl);
		else
			exec(self->value.s_cmd.word->value.word, ctl);
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
	char	**args;
	char	**path;
	char	**env;
	char	*cmd_path;

	if (cmd)
	{
		args = wordl_to_array(cmd);
		path = get_path(ctl->var_list);
		cmd_path = get_file_path(path, args[0]);
		env = get_env(ctl->var_list);
		execve(cmd_path, args, env);
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
