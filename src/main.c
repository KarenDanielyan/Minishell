/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/22 16:42:16 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"
#include <sys/wait.h>

static void	wait_and_reset(t_control *ctl);

int		*g_estat = NULL;

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
	system("leasks minishell");
}

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

static void	wait_and_reset(t_control *ctl)
{
	while (wait(&(ctl->estat)) != -1)
		;
	set_ecode(ctl);
	visit(NULL, ctl->tree, drop);
	free(ctl->input);
	dup2(ctl->in_dup, STDIN_FILENO);
	dup2(ctl->out_dup, STDOUT_FILENO);
}
