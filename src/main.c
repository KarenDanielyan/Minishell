/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 23:40:33 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"
#include <sys/wait.h>

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
		while (wait(&(ctl->estat)) != -1)
			;
		set_ecode(ctl);
		visit(NULL, ctl->tree, drop);
		free(ctl->input);
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
