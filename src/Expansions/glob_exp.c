/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/20 00:54:24 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

static void	replace(t_wordl **head, t_wordl *to_replace, t_wordl *replace_with);
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
	t_wordl	*head;
	t_wordl	*args;
	t_wordl	*temp;
	t_wordl	*next;

	args =  wordl_dup(node->value.word);
	args = make_word(args);
	head = args;
	while (args)
	{
		next = args->next;
		if (is_glob_required(args)) 
		{
			quote_remove(args->word);
			temp = apply(args->word);
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


int wildcard_match(const char *pattern, const char *string) 
{
	const char *p = NULL;
	const char *s = NULL;
	int star = 0;

	while (*string != '\0')
	{
		if ( *pattern == *string)
		{
			pattern++;
			string++;
		} 
		else if (*pattern == '*')
		{
			star = 1;
			p = pattern++;
			s = string;
		} 
		else if (star)
		{
			pattern = p + 1;
			string = ++s;
		}
		else
			return 0;
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

static t_wordl *apply(t_word *args)
{	
 	DIR *dir;
	t_wordl *word;
	struct dirent *entry;

	word = NULL;
	dir = opendir(".");
	
	if (dir == NULL)
	{
		perror("Unable to open directory");
 		exit(EXIT_FAILURE);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')//hastat chi entry->d_type != DT_DIR es pah@
			if (wildcard_match(args->value, entry->d_name))
				wordl_push_back(&word, word_new(entry->d_name, args->flags | W_FILEEXP));
	}
	closedir(dir);
	return (word);
}

/**
 * @brief	quote_remove() removes quotes from the word.
 * 
 */
static void	quote_remove(t_word *word)
{
	char	*s;
	char	*unquoted_word;
	int		quote_lvl;
	
	
	unquoted_word = NULL;
	s = word->value;
	quote_lvl = 0;
	while (*s)
	{
		if (*s == DQUOTE && !(quote_lvl & W_SQUOTE))
			quote_lvl = quote_lvl ^ W_DQUOTE;
		else if (*s == SQUOTE && !(quote_lvl & W_DQUOTE))
			quote_lvl = quote_lvl ^ W_SQUOTE;
		else
			ft_strappend(&unquoted_word, *s);
		s++;
	}
	free(word->value);
	word->value = unquoted_word;
}

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