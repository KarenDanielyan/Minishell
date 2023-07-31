/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/31 18:28:01 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"
#include <sys/wait.h>

static void	wait_and_reset(t_control *ctl, int after_exec);
static void	true_loop(t_control *ctl);

int		g_estat = 0;

int	main(int ac, char **av, char **env)
{
	t_control	ctl;

	ctl = init(ac, av, env);
	true_loop(&ctl);
	lst_clear(&(ctl.var_list), &free);
	flist_clear(ctl.built_ins);
	close(ctl.in_dup);
	close(ctl.out_dup);
	return (0);
}

/**
 * @brief	Readline while loop
 */
static void	true_loop(t_control *ctl)
{
	int		after_exec;

	while (1)
	{
		after_exec = FALSE;
		ctl->input = get_line(ctl, ctl->hist_fd);
		ctl->scanner = lex(ctl);
		ctl->tree = parse(ctl->scanner, ctl);
		if (ctl->tree)
		{
			execute(ctl, ctl->tree);
			after_exec = TRUE;
		}
		wait_and_reset(ctl, after_exec);
	}
}

static void	wait_and_reset(t_control *ctl, int after_exec)
{
	while (wait(&(*(ctl->estat))) != -1)
		;
	ctl->cur_pid = -42;
	set_ecode(ctl, after_exec);
	ctl->execute = EXIT_SUCCESS;
	visit(NULL, ctl->tree, drop);
	free(ctl->input);
	dup2(ctl->in_dup, STDIN_FILENO);
	dup2(ctl->out_dup, STDOUT_FILENO);
	unlink(HERE_FILE);
}
