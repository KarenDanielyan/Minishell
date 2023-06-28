/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:32:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/28 20:24:42 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	hist = ft_strjoin(getenv("HOME"), HISTFILE);
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup("?=0")));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(IFS)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS1)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS2)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strdup(PS4)));
	lst_push_back(&var_list, lst_new(SHELL, ft_strjoin("HISTFILE=", hist)));
	free(hist);
	return (var_list);
}
