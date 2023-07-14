/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/14 23:48:09 by dohanyan         ###   ########.fr       */
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
			quote_remove(args->word);
			temp = apply(args->word);
			// while (temp)
			// {
			// 	printf("----%s\n",temp->word->value);
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

char *reverce_str(char *str)
{
	int len;
	int i;
	char s1;

	len = ft_strlen(str);
	i = 0;
	int j = len - 1;
	while (i < len / 2)
	{
		s1 = str[i];
		str[i] = str[j];
		str[j] = s1;
		i++;
		j--;
	}
	return (str);
}

static t_wordl *apply(t_word *args)
{	
	struct dirent	*temp;
	DIR				*dir;
	t_wordl			*word;
	char			*to_reverce;
	char			*to_find;
	char 			**split;
	char			*res;
	int				first_flag;
	int				end_flag;
	int				i;

	dir = opendir(".");
	
	to_reverce = NULL;
	char *line = NULL;
	split = NULL;
	first_flag = 0;
	to_find = NULL;
	end_flag = 0;
	word = NULL;
	res = NULL;
	i = 0;

	if (args->value[0] == WILDCARD)
		first_flag = 1;
	if(args->value[ft_strlen(args->value) - 1] == WILDCARD)
		end_flag = 1;
	split = ft_split(args->value, WILDCARD);
	while (1)
	{
		temp = readdir(dir);
		if (temp != NULL)
		to_find =  temp->d_name;
		if (temp == NULL)
			break;
		line = ft_strdup(temp->d_name);
		while (split[i])
		{
			if(!first_flag )
			{
				res = ft_strnstr(to_find, split[i],ft_strlen(split[i]));
				if (res == NULL)
					break;
				to_find = res;
			}
			if(!end_flag)
			{
				to_find = reverce_str(to_find);
				to_reverce = reverce_str(split[ft_strlen_2d((const char **)split) - 1]);
				res = ft_strnstr(to_find, to_reverce, ft_strlen(to_reverce));
				if (res == NULL)
					break;
				res = reverce_str(res);
				split[ft_strlen_2d((const char **)split) - 1] = reverce_str(split[ft_strlen_2d((const char **)split) - 1]);
				to_find = res;
			}
			if (split[i])
			{
				res = ft_strstr(to_find, split[i]);
				if (res == NULL)
					break;
				to_find = res;
			}
				i++;
		}
		if (i == ft_strlen_2d((const char **)split))
				wordl_push_back(&word,word_new(line, args->flags | W_FILEEXP));
		i = 0;
		free(line);
	}
	while (word)
	{
		printf("%s\n",word->word->value);
		word = word->next;
	}
	
	free_2d(split);
	closedir(dir);
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