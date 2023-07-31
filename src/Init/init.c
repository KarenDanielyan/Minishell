/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:10:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/30 18:25:28 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"

/* TODO: Proper non-interactive mode */
t_control	init(int ac, char **av, char **env)
{
	t_control	ctl;
	char		*filename;

	(void)av;
	if (ac != 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: non-interactive mode is not \
supported.\n");
		exit(EXIT_FAILURE);
	}
	print_logo();
	rl_readline_name = "Minishell";
	ctl.cur_pid = -42;
	ctl.estat = &g_estat;
	ctl.execute = 0;
	ctl.in_dup = dup(STDIN_FILENO);
	ctl.out_dup = dup(STDOUT_FILENO);
	ctl.var_list = env_init(env);
	ctl.built_ins = builtin_init();
	filename = lst_get_by_key(ctl.var_list, "HISTFILE")->value;
	ctl.hist_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	sig_init();
	return (ctl);
}
