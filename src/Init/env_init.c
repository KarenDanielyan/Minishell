/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:32:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 15:34:48 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	init_shlvl(t_list	*var_list);
static void	init_oldpwd(t_list *var_list);
static void	init_vars(t_list **var_list);

t_list	*env_init(char **env)
{
	t_list	*var_list;

	var_list = NULL;
	while (*env)
	{
		lst_push_back(&var_list, lst_new(EXPORT, ft_strdup(*env)));
		env ++;
	}
	init_vars(&var_list);
	return (var_list);
}

static void	init_vars(t_list **var_list)
{
	char	*hist;

	init_shlvl(*var_list);
	init_oldpwd(*var_list);
	hist = ft_strjoin("TILDE=", getenv("HOME"));
	lst_push_back(var_list, lst_new(PRIVATE, hist));
	if (!lst_get_by_key(*var_list, IFS))
		lst_push_back(var_list, lst_new(SHELL, ft_strdup(IFS_INIT)));
	lst_push_back(var_list, lst_new(SHELL, ft_strdup("?=0")));
	lst_push_back(var_list, lst_new(SHELL, ft_strdup(PS1)));
	lst_push_back(var_list, lst_new(SHELL, ft_strdup(PS2)));
	lst_push_back(var_list, lst_new(SHELL, ft_strdup(PS4)));
	hist = ft_strjoin(getenv("HOME"), HISTFILE);
	lst_push_back(var_list, lst_new(PRIVATE, ft_strjoin("HISTFILE=", hist)));
	free(hist);
}

static void	init_shlvl(t_list	*var_list)
{
	t_list		*shlvl;
	int64_t		atoi;
	char		*value;
	char		*res;

	res = NULL;
	value = NULL;
	shlvl = lst_get_by_key(var_list, SHLVL);
	if (shlvl)
		value = shlvl->value;
	else
		value = "0";
	atoi = ft_atol(value);
	if (atoi >= 1000)
	{
		ft_dprintf(STDERR_FILENO, ERR_SHLVL, (atoi + 1));
		atoi = 1;
	}
	else if (atoi < 0)
		atoi = 0;
	else
		atoi = atoi % 1000 + 1;
	res = ft_itoa(atoi);
	lst_set(var_list, EXPORT, SHLVL, res);
	free(res);
}

static void	init_oldpwd(t_list *var_list)
{
	t_list	*oldpwd;

	oldpwd = lst_get_by_key(var_list, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->joined);
		free(oldpwd->value);
		oldpwd->joined = NULL;
		oldpwd->value = NULL;
	}
	else
		lst_set(var_list, EXPORT, "OLDPWD", NULL);
}
