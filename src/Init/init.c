/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:32:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/02 16:10:03 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_init(char **env)
{
	t_list	*var_list;

	var_list = NULL;
	while (*env)
	{
		lst_push_back(&var_list, lst_new(EXPORT, *env));
		env ++;
	}
	lst_push_back(&var_list, lst_new(SHELL, IFS));
	lst_push_back(&var_list, lst_new(SHELL, PS1));
	lst_push_back(&var_list, lst_new(SHELL, PS2));
	lst_push_back(&var_list, lst_new(SHELL, PS4));
	return (var_list);
}
