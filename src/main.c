/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/07 16:54:44 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "lex.h"
#include "minishell.h"

static void	switch_case(t_list *var_list, char *str)
{
	t_wordl *wordl;
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

int check_cooats(t_wordl *args)
{
	while (args->word)
	{
		if(ft_strchr(args->word->value, DQUOTE)== NULL || ft_strrchr(args->word->value, DQUOTE))
		{
			ft_dprintf(STDERR_FILENO,"minishell quote is not close\n");
			return (0);
		}
		args = args->next;
	}
	return (1);
}

void check_tokens(t_token *scanner)
{
	int flag;
	t_token *temp;
	int count_subshell;

	flag = 0;
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
			if (!check_cooats(temp->wordl))
				break;
		}
		temp = temp->next;
	}
}

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
		tree = parse(scanner);
		visit(tree, check_syntax);
		visit(tree, drop);
		switch_case(var_list,str);
		free(str);
		//system("leaks minishell");
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
