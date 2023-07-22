/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:32:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 16:47:18 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	init_shlvl(t_list	*var_list);

t_list	*env_init(char **env)
{
	t_list	*var_list;
	char	*hist;

	var_list = NULL;
	while (*env)
	{
		lst_push_back(&var_list, lst_new(EXPORT, ft_strdup(*env)));
		env ++;
	}
	hist = ft_strjoin("TILDE=", getenv("HOME"));
	lst_push_back(&var_list, lst_new(PRIVATE, hist));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup("?=0")));
	if (!lst_get_by_key(var_list, IFS))
		lst_push_back(&var_list, lst_new(SHELL, ft_strdup(IFS_INIT)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS1)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS2)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS4)));
	hist = ft_strjoin(getenv("HOME"), HISTFILE);
	lst_push_back(&var_list, lst_new(SHELL, ft_strjoin("HISTFILE=", hist)));
	free(hist);
	init_shlvl(var_list);
	return (var_list);
}

static void	init_shlvl(t_list	*var_list)
{
	t_list	*shlvl;
	char	*value;
	char	*res;

	res = NULL;
	value = NULL;
	shlvl = lst_get_by_key(var_list, SHLVL);
	if (shlvl)
		value = shlvl->value;
	else
		value = "0";
	res = ft_itoa((ft_atoi(value) % 1000) + 1);
	lst_set(var_list, EXPORT, SHLVL, res);
	free(res);
}
