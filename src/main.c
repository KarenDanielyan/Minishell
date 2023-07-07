/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/07 21:25:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "lex.h"
#include "minishell.h"

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
void	true_loop(t_list *var_list, int fd)
{
	char	*str;
	t_token	*scanner;
	t_node	*tree;

	sig_init();
	while (1)
	{
		str = get_line(var_list, fd);
		if (!str)
			continue ;
		scanner = lex(str);
		tree = parse(scanner);
		visit(tree, check_syntax);
		visit(tree, drop);
		switch_case(var_list, str);
		free(str);
	}
}

/* TODO: proper non-Interactive mode */
int	main(int ac, char **av, char **env)
{
	int		fd;
	t_list	*var_list;
	char	*filename;

	print_logo();
	rl_readline_name = "Minishell";
	rl_instream = stdin;
	if (isatty(STDERR_FILENO))
		rl_outstream = stderr;
	mode_init(ac, av);
	var_list = env_init(env);
	filename = lst_get_by_key(var_list, "HISTFILE")->value;
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	true_loop(var_list, fd);
	lst_clear(&var_list, &free);
	return (0);
}
