/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:58:17 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/21 19:04:02 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

static int	handle_suffix(t_control *ctl, t_node *self, int pid);
static void	handle_builtin_modes(t_control *ctl, t_node *self, \
	t_flist *builtin, int pid);

void	handle_builtin(t_control *ctl, t_node *self, t_flist *buitltin)
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
	handle_builtin_modes(ctl, self, buitltin, pid);
}

void	handle_command(t_control *ctl, t_node *self)
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
		handle_suffix(ctl, self, pid);
	}
	if (self->value.s_cmd.in_fd != STDIN_FILENO)
		close(self->value.s_cmd.in_fd);
	if (self->value.s_cmd.out_fd != STDOUT_FILENO)
		close(self->value.s_cmd.out_fd);
	if (pid == 0)
		execute_and_check(cmd, args, env);
	free(cmd);
	free(env);
	free_2d(args);
}

static void	handle_builtin_modes(t_control *ctl, t_node *self, \
	t_flist *builtin, int pid)
{
	int	estat;

	if (pid == 0 || pid == -42)
	{
		if (handle_suffix(ctl, self, pid) == EXIT_FAILURE)
			return ;
		if (builtin)
			estat = builtin->cmd(self->value.s_cmd.word->value.word, ctl);
		else
			estat = set(self->value.s_cmd.word->value.word, ctl);
	}
	if (pid == 0)
		exit(estat);
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
