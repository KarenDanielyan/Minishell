/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/13 00:18:46 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

// static void	replace(t_wordl *head, t_wordl *to_replace, t_wordl *replace_with);
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
			printf("%d\n",__LINE__);
			quote_remove(args->word);
			printf("%d\n",__LINE__);
			temp = apply(args->word);
			printf("%d\n",__LINE__);
			// while (temp)
			// {
			// 	printf("%s\n",temp->word->value);
			// 	temp = head->next;
			// }
			
			//replace(head, args, temp);
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
	return (0);
}

static t_wordl *apply(t_word *args)
{
	int				i;
	int				j;
	char			*res;
	char			*str;
	DIR				*dir;
	struct dirent	*temp;
	t_wordl			*word;
	char 			**split;
	int				first_flag;
	int				end_flag;
			printf("%d\n",__LINE__);

	first_flag = 0;
	end_flag = 0;
	dir = opendir(".");
	word = NULL;
	i = 0;
	j = 0;
	str = NULL;
	res = NULL;
	
	if (args->value[0] == WILDCARD)
		first_flag = 1;
	if(args->value[ft_strlen(args->value) - 1] == WILDCARD)
		end_flag = 1;
	split = ft_split(args->value, WILDCARD);
	while (1)
	{
		temp = readdir(dir);
		str = temp->d_name;
		if (str == NULL)
			break;
		while (str[i])
		{
						printf("%d\n",__LINE__);

			if (args->value[i] == WILDCARD)
				i++;
			printf("%d\n",__LINE__);
			while (str[i + j] == args->value[j] && str[i + j])
				j++;
						printf("%d\n",__LINE__);
			if (args->value[j] == '\0')
			{
				printf("%d\n",__LINE__);
				wordl_push_back(&word, word_new(str, (W_FILEEXP | args->flags)));
				printf("------------%s\n",str);
			}
						printf("%d\n",__LINE__);

			i++;
			j = 0;
		}
		free (str);
		i = 0;
		j = 0;
	}
	return (word);
}

// while (str[i] != '\0')
// 	{
// 		while (str[i + j] == to_find[j] && str[i + j] != '\0')
// 		{
// 			j++;
// 		}
// 		if (to_find[j] == '\0')
// 			return (str + i);
// 		i++;
// 		j = 0;
// 	}

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

// static void	replace(t_wordl *head, t_wordl *to_replace, t_wordl *replace_with)
// {
	
// }