/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:42:52 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/30 15:57:21 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "list.h"

static int	get_env_len(t_list *var_list);

char	**get_env(t_list	*var_list)
{
	char	**envp;
	char	**tmp;

	envp = (char **)malloc((get_env_len(var_list) + 1) * sizeof(char *));
	tmp = envp;
	while (var_list)
	{
		if (var_list->type == EXPORT)
		{
			*tmp = var_list->joined;
			tmp ++;
		}
		var_list = var_list->next;
	}
	return (envp);
}

static int	get_env_len(t_list *var_list)
{
	int		len;

	len = 0;
	while (var_list)
	{
		if (var_list->type == EXPORT)
			len ++;
		var_list = var_list->next;
	}
	return (len);
}
