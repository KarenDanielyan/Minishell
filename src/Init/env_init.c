/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:32:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/09 18:46:41 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

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
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(IFS)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS1)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS2)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS4)));
	hist = ft_strjoin(getenv("HOME"), HISTFILE);
	lst_push_back(&var_list, lst_new(SHELL, ft_strjoin("HISTFILE=", hist)));
	free(hist);
	return (var_list);
}
