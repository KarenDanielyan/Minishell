/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:59:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/03 19:24:48 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

void	lst_set(t_list *var_list, char *key, char *value)
{
	char	*tmp;

	while(var_list)
	{
		if (ft_strcmp(var_list->key, key) == 0)
		{
			free(var_list->joined);
			free(var_list->value);
			var_list->value=value;
			tmp = ft_strjoin(key, "=");
			var_list->joined = ft_strjoin(tmp, value);
			break;
		}
		var_list = var_list->next;
	}
	if (!var_list)
	{
		tmp = ft_strjoin(key, "=");
		lst_push_back(&var_list, lst_new(EXPORT, ft_strjoin(tmp, value)));
	}
	free(tmp);
	// key = NULL;
}