/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/20 23:36:50 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

static int		is_glob_required(t_wordl *head);
static t_wordl	*apply(t_word *args);
static void		replace(t_wordl **head, t_wordl *to_replace, \
				t_wordl *replace_with);

/**
 * @brief		glob_exp() performes filename expansion on the provided word.
 * 				This is very simplistic implementation of shell 
 * 				filename expansion. It only performs it on current working
 * 				directory.
 * 				The only pattern supported is `*` <asterisk>, which matches 
 * 				any string, including the null string.
 *
 * @param node	The node on which the filename expansion is applied.
 */
void	glob_exp(t_node *node)
{
	t_wordl	*head;
	t_wordl	*args;
	t_wordl	*temp;
	t_wordl	*next;

	args = wordl_dup(node->value.word);
	head = args;
	while (args)
	{
		next = args->next;
		if (is_glob_required(args))
		{
			remove_quotes(args->word);
			temp = apply(args->word);
			if (temp)
				replace(&head, args, temp);
		}
		args = next;
	}
	wordl_clear(node->value.word);
	node->value.word = head;
}

/**
 * @brief		is_glob_required() will check whether filename expansion
 * 				is required on the provided word.
 * 
 * 
 * @param head	The word node we check.
 * @return int	Returns 1 if filename expansion should be applied,
 * 				0 otherwise.
 */
static int	is_glob_required(t_wordl *head)
{
	int		quote_lvl;
	char	*s;

	s = head->word->value;
	quote_lvl = 0;
	if (!(head->word->flags & W_ASSIGNMENT))
	{
		while (*s)
		{
			if (*s == SQUOTE && !(quote_lvl & W_DQUOTE))
				quote_lvl = quote_lvl ^ W_SQUOTE;
			if (*s == DQUOTE && !(quote_lvl & W_SQUOTE))
				quote_lvl = quote_lvl ^ W_DQUOTE;
			if (*s == WILDCARD && !quote_lvl)
				return (1);
			s++;
		}
	}
	return (0);
}

static t_wordl	*apply(t_word *args)
{	
	DIR				*dir;
	t_wordl			*word;
	struct dirent	*entry;

	word = NULL;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (ft_strchr(args->value, DOT) || entry->d_name[0] != '.')
			if (wildcard_match(args->value, entry->d_name))
				wordl_push_back(&word, \
					word_new(entry->d_name, args->flags | W_FILEEXP));
	}
	closedir(dir);
	return (word);
}

/**
 * @brief	quote_remove() removes quotes from the word.
 * 
 */

static void	replace(t_wordl **head, t_wordl *to_replace, t_wordl *replace_with)
{
	t_wordl	*prev;
	t_wordl	*next;

	prev = wordl_find_prev(*head, to_replace);
	next = to_replace->next;
	if (prev)
		prev->next = replace_with;
	else
		*head = replace_with;
	wordl_last(replace_with)->next = next;
	to_replace->next = NULL;
	wordl_clear(to_replace);
}
