/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/19 16:03:43 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "lex.h"
#include "minishell.h"
#include "debug.h"
#include <sys/wait.h>

static void	switch_case(t_list *var_list, char *str)
{
	t_wordl	*wordl;
	char	**split;
	int		i;

	split = ft_split(str, ' ');
	wordl = NULL;
	i = -1;
	while (split[++i])
		wordl_push_back(&wordl, word_new(*(split + i), 0));
	if (ft_strcmp(wordl->word->value, "history") == 0)
		history(wordl, var_list);
	if (ft_strcmp(wordl->word->value, "cd") == 0)
		cd(wordl, var_list);
	if (ft_strcmp(wordl->word->value, "echo") == 0)
		echo(wordl);
	if (ft_strcmp(wordl->word->value, "exit") == 0)
		my_exit(var_list, wordl);
	if (ft_strcmp(wordl->word->value, "pwd") == 0)
		pwd();
	if (ft_strcmp(wordl->word->value, "unset") == 0)
		unset(&var_list, wordl);
	if (ft_strcmp(wordl->word->value, "export") == 0)
		export(var_list, wordl);
	if (ft_strcmp(wordl->word->value, "env") == 0)
		env(var_list);
	free_2d(split);
	wordl_clear(wordl);
}

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
		while (wait(NULL) != -1)
			;
		print_tree(ctl->tree, "", 1);
		switch_case(ctl->var_list, ctl->input);
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
