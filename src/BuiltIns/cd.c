/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:29:40 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/25 23:48:59 by dohanyan         ###   ########.fr       */
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

	if (!lst_get_by_key(var_list, "PWD"))
		return ;
	if (!lst_get_by_key(var_list, "HOME"))
	{
		ft_dprintf(STDERR_FILENO, "bash: cd: HOME not set\n");
		return ;
	}
	if (!path)
		path = lst_get_by_key(var_list,"HOME")->value;
	current_pwd = ft_strdup(lst_get_by_key(var_list, "PWD")->value);
	if (chdir(path) != 0)
		perror("bash: cd");
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		perror("getcwd()");
	lst_set(var_list, "PWD", new_pwd);
	lst_set(var_list, "OLDPWD", current_pwd);
}
