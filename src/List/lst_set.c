/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:59:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/12 14:26:08 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>
#include <stdio.h>

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
	while (i)
	{
		if (ft_strcmp(i->key, key) == 0)
		{
			free(i->joined);
			free(i->value);
			i->value = value;
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
	free(tmp);
}