/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:44:43 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 21:47:02 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include <libft.h>
#include <stdio.h>

static void		handle_builtin(t_control *ctl, t_node *self, t_flist *builtin);
static int		handle_suffix(t_control *ctl, t_node *self, int pid);
static void		handle_command(t_control *ctl, t_node *self);
static t_flist	*get_builtin(t_control *ctl, t_node *word);

void	execute_scommand(t_control *ctl, t_node *self)
{
	t_flist	*builtin_cmd;

	builtin_cmd = get_builtin(ctl, self->value.s_cmd.word);
	if (builtin_cmd || is_assignment(self->value.s_cmd.word->value.word->word))
		handle_builtin(ctl, self, builtin_cmd);
	else
		handle_command(ctl, self);
}

static void handle_builtin(t_control *ctl, t_node *self, t_flist *builtin)
{
	int	pid;

	pid = -42;
	if (self->value.s_cmd.word->value.word->word->flags & W_SUBSHELL_PIPE)
		pid = my_fork();
	if (pid == 0 || pid == -42)
	{
		dup2(self->value.s_cmd.in_fd, STDIN_FILENO);
		dup2(self->value.s_cmd.out_fd, STDOUT_FILENO);
	}
	if (self->value.s_cmd.in_fd != STDIN_FILENO)
		close(self->value.s_cmd.in_fd);
	if (self->value.s_cmd.out_fd != STDOUT_FILENO)
		close(self->value.s_cmd.out_fd);
	if (pid == 0 || pid == -42)
	{
		if (handle_suffix(ctl, self, pid) == EXIT_FAILURE)
			return ;
		if (builtin)
			builtin->cmd(self->value.s_cmd.word->value.word, ctl);
		else
			set(self->value.s_cmd.word->value.word, ctl);
	}
}

static void	handle_command(t_control *ctl, t_node *self)
{
	int		pid;
	char	**args;
	char	**env;
	char	*cmd;

	args = wordl_to_array(self->value.s_cmd.word->value.word);
	env = get_env(ctl->var_list);
	cmd = cmd_search(self->value.s_cmd.word->value.word, ctl->var_list);
	pid = my_fork();
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
		handle_suffix(ctl, self, pid);
		execute_and_check(cmd, args, env);
	}
	free(cmd);
	free(env);
	free_2d(args);
}

static int	handle_suffix(t_control *ctl, t_node *self, int pid)
{
	if (execute(ctl, self->value.s_cmd.suffix) == EXIT_FAILURE)
	{
		if (pid == 0)
			exit(EXIT_FAILURE);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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

