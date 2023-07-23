/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/23 14:49:51 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"
#include <sys/wait.h>

static void	wait_and_reset(t_control *ctl);
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
	while (1)
	{
		ctl->input = get_line(ctl, ctl->hist_fd);
		if (!ctl->input)
			continue ;
		ctl->scanner = lex(ctl->input, ctl->var_list);
		if (ctl->scanner == NULL)
		{
			free(ctl->input);
			continue ;
		}
		ctl->tree = parse(ctl->scanner, ctl);
		if (ctl->tree == NULL)
		{
			free(ctl->input);
			continue ;
		}
		execute(ctl, ctl->tree);
		printf("%d\n", *(ctl->estat));
		wait_and_reset(ctl);
	}
}

static void	wait_and_reset(t_control *ctl)
{
	while (wait(&(*(ctl->estat))) != -1)
		;
	set_ecode(ctl, TRUE);
	ctl->execute = EXIT_SUCCESS;
	visit(NULL, ctl->tree, drop);
	free(ctl->input);
	dup2(ctl->in_dup, STDIN_FILENO);
	dup2(ctl->out_dup, STDOUT_FILENO);
	unlink(HERE_FILE);
}
