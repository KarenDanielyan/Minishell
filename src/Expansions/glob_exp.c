/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/16 16:29:40 by dohanyan         ###   ########.fr       */
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
			replace(&head, args, temp);
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
	int 			mgea_flag;
	int 			rem1;
	int				rem2;

	dir = opendir(".");
	to_reverce = NULL;
	char *line = NULL;
	split = NULL;
	first_flag = 0;
	to_find = NULL;
	end_flag = 0;
	word = NULL;
	res = NULL;
	mgea_flag = 0;
	i = 0;

	if (args->value[0] == WILDCARD)
		first_flag = 1;
	if(args->value[ft_strlen(args->value) - 1] == WILDCARD)
		end_flag = 1;
	split = ft_split(args->value, WILDCARD);
	rem1 = first_flag;
	rem2 = end_flag;
	while (1)
	{
		first_flag =rem1;
		end_flag = rem2;
		mgea_flag = 0;
		temp = readdir(dir);
		if (temp)
		to_find =  temp->d_name;
		if (temp == NULL)
			break;
		line = ft_strdup(temp->d_name);
		printf("%s\n",line);
		while (split[i])
		{
			if(!first_flag && split[i])
			{
				printf("do res = %s\n",res);
				res = ft_strnstr(to_find, split[i],ft_strlen(split[0]));
				if(res != NULL)
				res +=ft_strlen(split[0]);
				printf("posel res = %s\n",res);
				if (res == NULL)
					break;
				to_find = res;
				first_flag = 1;
				i++;
			}
			if(!end_flag && split[i])
			{
				to_find = reverce_str(to_find);
				to_reverce = reverce_str(split[ft_strlen_2d((const char **)split) - 1]);
				printf("do res = %s\n",res);
				res = ft_strnstr(to_find, to_reverce, ft_strlen(to_reverce));
				if(res != NULL)
				res +=ft_strlen(to_reverce);
				if (res == NULL)
					break;
				res = reverce_str(res);
				printf("do res = %s\n",res);
				split[ft_strlen_2d((const char **)split) - 1] = reverce_str(to_reverce);
				to_find = res;
				end_flag = 1;
				mgea_flag = 1;
				i++;
			}
			if(split[i])
			{
				if (mgea_flag == 1)
					i--;
				printf("do res = %s\n",res);
				res = (ft_strstr(to_find, split[i]));
				printf("posle res = %s\n",res);
				if (res != NULL)
					res++;
				if (res == NULL)
					break;
				to_find = res;
				if (mgea_flag == 1)
					i+=2;
				else
					i++;
			}
		}
		if (i == ft_strlen_2d((const char **)split))
				wordl_push_back(&word,word_new(line, args->flags | W_FILEEXP));
			// printf("%s\n",line);
		i = 0;
		free(line);
	}

	free_2d(split);
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
	wordl_clear(to_replace);
	*head = replace_with;
}