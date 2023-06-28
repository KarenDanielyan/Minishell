/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/28 20:31:13 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void free_tokl(t_tokl *tokens)
// {
// 	t_tokl	*rem;

// 	rem = NULL;
// 	while (tokens)
// 	{
// 		rem = tokens->next;
// 		free(tokens->word->value);
// 		free(tokens->word);
// 		free(tokens);
// 		tokens = rem;
// 	}
// }

t_wordl *add_toempty(t_wordl *node, t_word *word)
{
	node = (t_wordl *)malloc(sizeof(t_wordl));
	node->next = NULL;
	node->word = word;
	return (node);
}

t_wordl *push_back(t_wordl *node,t_word *word)
{
	t_wordl *rem;
	t_wordl *tp;
	
	rem = node;
	tp = NULL;
	if (node == NULL)
	{
		node = add_toempty(node, word);
		return (node);
	}
	tp = add_toempty(tp, word);	
	while(rem->next)
		rem = rem->next;
	rem->next = tp;
	return (node);
}

t_word *add_word(t_word *word,char *value,int type,int flag)
{
	word = (t_word *)malloc(sizeof(t_word));
	word->flags = flag;
	word->type = type;
	word->value = value;
	return (word);
}

static void	switch_case(t_list *var_list, char *str)
{
	char	**split;
	int i = 0;
	t_wordl *wordl;
	t_word *word;
	
	split = ft_split(str, ' ');
	wordl = NULL;
	word = NULL;
	(void)var_list;
	while (split[i]) 
	{
		word = add_word(word,split[i], WORD, 0);
		wordl = push_back(wordl, word);
		i++;
	}
	// while(wordl)
	// {
	// 	printf("%s\n",wordl->word->value);
	// 	wordl = wordl->next;
	// }
	if (ft_strcmp(wordl->word->value, "history") == 0)
		history(wordl,var_list);
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
	if (ft_strcmp(wordl->word->value, "env") == 0)
		env(var_list);
	free_2d(split);
}

/**
 * @brief	Readline while loop
 */
void	true_loop(t_list *var_list, int fd)
{
	char	*str;
	t_tokl	*tokens;

	tokens = NULL;
	sig_init();
	while (1)
	{
		str = readline(lst_get_by_key(var_list, "PS1")->value);
		if (!str)
		{
			write (2, "exit\n", 5);
			break ;
		}
		if (!(*str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		ft_putendl_fd(str, fd);
		//tokens = lex(str);
		switch_case(var_list, str);
	//	free_tokl(tokens);
		free(str);
	}
}

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
