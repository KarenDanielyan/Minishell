/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:29:40 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/03 21:03:18 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param key 
 * @param value Use strdup before passing the argument.
 */
void	cd(const char *path, t_list *var_list)
{
	char	*current_pwd;
	char	*new_pwd;
	
	current_pwd = ft_strdup(lst_get_by_key(var_list, "PWD")->value);
	if (chdir(path) != 0)
		perror("bash: cd: a");
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		perror("getcwd()");
	lst_set(var_list, "PWD", new_pwd);
	lst_set(var_list, "OLDPWD", current_pwd);
}
