/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 19:13:55 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"
#include <sys/wait.h>

static void	wait_and_reset(t_control *ctl);

/**
 * @brief	Readline while loop
 */
void	true_loop(t_control *ctl)
{
	while (1)
	{
		ctl->input = get_line(ctl->var_list, ctl->hist_fd);
		if (!ctl->input)
			continue ;
		ctl->scanner = lex(ctl->input, ctl->var_list);
		if (ctl->scanner == NULL)
		{
			free(ctl->input);
			continue ;
		}
		ctl->tree = parse(ctl->scanner, ctl->var_list);
		if (ctl->tree == NULL)
		{
			free(ctl->input);
			continue ;
		}
		execute(ctl, ctl->tree);
		wait_and_reset(ctl);
	}
}

int	main(int ac, char **av, char **env)
{
	t_control	ctl;

	ctl = init(ac, av, env);
	true_loop(&ctl);
	lst_clear(&(ctl.var_list), &free);
	flist_clear(ctl.built_ins);
	return (0);
}

static void	wait_and_reset(t_control *ctl)
{
	int	in;
	int	out;

	while (wait(&(ctl->estat)) != -1)
		;
	set_ecode(ctl);
	visit(NULL, ctl->tree, drop);
	free(ctl->input);
	in = open("/dev/stdin", O_RDONLY);
	out = open("/dev/stdout", O_TRUNC | O_WRONLY);
	dup2(in , STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}
