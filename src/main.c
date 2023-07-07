/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/08 02:46:59 by kdaniely         ###   ########.fr       */
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


int check_quotes(t_wordl *args)
{
	while (args)
	{
		if (ft_strchr(args->word->value, DQUOTE))
		{
			if (ft_strchr(args->word->value, DQUOTE) == ft_strrchr(args->word->value, DQUOTE))
			{
				ft_dprintf(STDERR_FILENO, "%s", ERROR_QUOTES);
				return (0);
			}
		}
		if (ft_strchr(args->word->value, SQUOTE))
		{
			if (ft_strchr(args->word->value, SQUOTE) == ft_strrchr(args->word->value, SQUOTE))
			{
				ft_dprintf(STDERR_FILENO, "%s", ERROR_QUOTES);
				return (0);
			}
		}
		args = args->next;
	}
	return (1);
}

void check_tokens(t_token *scanner)
{
	t_token	*temp;
	int		count_subshell;

	temp = scanner;
	count_subshell = 0;
	while (temp)
	{
		if (temp->type == SUBSHELL_OPEN)
			count_subshell++;
		if (temp->type == SUBSHELL_CLOSE)
			count_subshell--;
		if (temp->type == WORD)
		{
			if (!check_quotes(temp->wordl))
				return ;
		}
		temp = temp->next;
	}
	if (count_subshell != 0)
		ft_dprintf(STDERR_FILENO, "%s\n", ERROR_PAREN);
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
		check_tokens(scanner);
		tree = parse(scanner, var_list);
		if (tree == NULL)
			continue ;
		switch_case(var_list,str);
		visit(tree, drop);
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
