/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:32:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/30 16:00:00 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_init(char **env)
{
	t_list	*var_list;

	while (env)
	{
		lst_push_back(&var_list, lst_new(EXPORT, *env));
		env ++;
	}
	return (var_list);
}
