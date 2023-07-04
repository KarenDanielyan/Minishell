/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:59:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/04 23:42:41by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>
#include <stdio.h>

#define EQUALS '='

/**
 * @brief 
 * 
 * @param var_list 
 * @param key 
 * @param value 
 * 
 * @var i is an iterator for variable list.
 */
void	lst_set(t_list *var_list, char *key, char *value)
{
	char	*tmp;
	t_list	*i;

	i = var_list;
	tmp = NULL;
	while (i)
	{
		if (ft_strcmp(i->key, key) == 0)
		{
			free(i->joined);
			free(i->value);
			i->value = value;
			if (ft_strchr(key, EQUALS))
				tmp = ft_strjoin(key, "=");
			i->joined = ft_strjoin(tmp, value);
			break ;
		}
		i = i->next;
	}
	if (i == NULL)
	{
		tmp = ft_strjoin(key, "=");
		lst_push_back(&var_list, lst_new(EXPORT, ft_strjoin(tmp, value)));
	}
	if (tmp)
		free(tmp);
}

/**
 * @brief	lst_set_by_word() sets a variable from assign_word
 * 			into a variablel list.
 * 
 * @param var_list 
 * @param key 
 * 
 * @var i is an iterator for variable list.
 */
void	lst_set_by_word(t_list *var_list, char *assign_word)
{
	char	**split;
	char	*tmp;
	t_list	*i;

	i = var_list;
	tmp = 0;
	split = ft_split(assign_word, EQUALS);
	while (i)
	{
		if (ft_strcmp(i->key, split[0]) == 0)
		{
			free(i->joined);
			free(i->value);
			i->value = split[1];
			if (ft_strchr(assign_word, EQUALS))
				tmp = ft_strjoin(split[0], "=");
			i->joined = ft_strjoin(tmp, split[1]);
			break ;
		}
		i = i->next;
	}
	if (i == NULL)
	{
		if (ft_strchr(assign_word, EQUALS))
			tmp = ft_strjoin(split[0], "=");
		lst_push_back(&var_list, lst_new(EXPORT, ft_strjoin(assign_word, split[1])));
	}
	if (tmp)
		free(tmp);
	free_2d(split);
}

