/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/11 23:14:16 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

static void	replace(t_wordl *head, t_wordl *to_replace, t_wordl *replace_with);
static int	is_glob_required(t_wordl *head);
static void	quote_remove(t_word *word);
static t_wordl	*apply(t_word *args);

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
	t_wordl	*args;
	t_wordl	*temp;
	t_wordl	*head;

	args =  wordl_dup(node->value.word);
	args = make_word(args);
	head = args;
	while (args)
	{
		if (is_glob_required(args)) 
		{
			quote_removal(args->word);
			temp = apply(args->word);
			replace(head, args, temp);
		}
		args = args->next;
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
	while (s)
	{
		if (*s == SQUOTE && !(quote_lvl & W_DQUOTE))
			quote_lvl = quote_lvl ˆ W_SQUOTE;
		if (*s == DQUOTE && !(quote_lvl & W_SQUOTE))
			quote_lvl = quote_lvl ˆ W_DQUOTE;
		if (*s == WILDCARD && !quote_lvl)
			return (1);
		s++;
	}
	return (0);
}

static t_wordl *apply(t_wordl *args)
{
	char *str;

	while (1)
	{
		if (str == NULL)
			break;
	}
	
}
