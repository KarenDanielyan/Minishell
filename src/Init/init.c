/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:10:22 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 22:05:31 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"

/* TODO: Proper non-interactive mode */
t_control	init(int ac, char **av, char **env)
{
	t_control	ctl;
	char		*filename;

	print_logo();
	rl_readline_name = "Minishell";
	rl_instream = stdin;
	if (isatty(STDERR_FILENO))
		rl_outstream = stderr;
	mode_init(ac, av);
	ctl.estat = 0;
	ctl.var_list = env_init(env);
	filename = lst_get_by_key(ctl.var_list, "HISTFILE")->value;
	ctl.hist_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	sig_init();
	return (ctl);
}


