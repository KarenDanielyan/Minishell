/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:42:52 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 17:42:05 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_len(t_list *var_list, int mode);

enum e_mode
{
	KEY,
	FULL
};

/**
 * @brief Get the environment as a string array.
 * 
 * @param var_list	A variable linked list.
 * @return char**	Environment variables represented as a string array.
 * 
 * WARN:			This array works directily with the variable list
 * 					and should not be freed.
 */
char	**get_env(t_list	*var_list)
{
	char	**envp;
	char	**tmp;

	envp = (char **)malloc((get_env_len(var_list, FULL) + 1) * sizeof(char *));
	tmp = envp;
	while (var_list)
	{
		if (var_list->type == EXPORT && var_list->joined)
		{
			*tmp = var_list->joined;
			tmp ++;
		}
		var_list = var_list->next;
	}
		*tmp = NULL;
	return (envp);
}

char	**get_env_key(t_list	*var_list)
{
	char	**envp;
	char	**tmp;

	envp = (char **)malloc((get_env_len(var_list, KEY) + 1) * sizeof(char *));
	tmp = envp;
	while (var_list)
	{
		if (var_list->type == EXPORT)
		{
			*tmp = var_list->key;
			tmp ++;
		}
		var_list = var_list->next;
	}
	*tmp = NULL;
	return (envp);
}

/**
 * @brief Get the number of environment variables.
 */
static int	get_env_len(t_list *var_list, int mode)
{
	int		len;

	len = 0;
	while (var_list)
	{
		if (var_list->type == EXPORT)
		{
			if (mode == FULL && var_list->joined)
				len ++;
			else if (mode == KEY)
				len ++;
		}
		var_list = var_list->next;
	}
	return (len);
}
