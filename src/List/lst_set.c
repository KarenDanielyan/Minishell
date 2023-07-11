/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:37:46 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/11 20:47:03 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include <libft.h>
#include <stdio.h>

#define EQUALS_S "="

/**
 * @brief	lst_set() sets or modifies a variable key inside
 * 			a variable list var_list with value.
 * 
 * @param var_list	The list where we put out variable.
 * @param key		Variable name.
 * @param value		Value to be set.
 * 
 * @var i is an iterator for variable list.
 */
void	lst_set(t_list *var_list, char *key, char *value)
{
	char	*tmp;
	t_list	*i;

	i = lst_get_by_key(var_list, key);
	if (value != NULL)
		tmp = ft_strjoin(key, EQUALS_S);
	else
		tmp = ft_strdup(key);
	if (i == NULL)
		lst_push_back(&var_list, lst_new(EXPORT, ft_strjoin(tmp, value)));
	else if (i->type != PRIVATE)
	{
		free(i->value);
		free(i->joined);
		i->value = ft_strdup(value);
		i->joined = ft_strjoin(tmp, value);
	}
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
	t_list	*var;

	split = get_key_value(assign_word);
	var = lst_get_by_key(var_list, split[0]);
	if (ft_strchr(assign_word, EQUALS))
		tmp = ft_strjoin(split[0], EQUALS_S);
	else
		tmp = ft_strdup(split[0]);
	if (var == NULL)
		lst_push_back(&var_list, lst_new(EXPORT, ft_strjoin(tmp, split[1])));
	else
	{
		free(var->value);
		free(var->joined);
		var->value = ft_strdup(split[1]);
		var->joined = ft_strjoin(tmp, split[1]);
	}
	free_2d(split);
	free(tmp);
}
