/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:29:40 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/03 16:32:13 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lst_get_by_key(t_list *var_list, char *key)
{
	while(var_list)
	{
		if (ft_strcmp(key, var_list->key) == 0)
			return (var_list);
		var_list = var_list->next;
	}	
	return (NULL);
}

/**
 * @brief 
 * 
 * @param key 
 * @param value Use strdup before passing the argument.
 */
void	lst_write(t_list *var_list, char *key, char *value)
{
	char	*tmp;

	while(var_list)
	{
		if (ft_strcmp(var_list->key, key) == 0)
		{
			free(var_list->joined);
			free(var_list->value);
			var_list->value=value;
			tmp = ft_strjoin(key, "=");
			var_list->joined = ft_strjoin(tmp, value);
		}
		var_list = var_list->next;
	}
	if (!var_list)
	{
		tmp = ft_strjoin(key, "=");
		lst_push_back(&var_list, lst_new(EXPORT, ft_strjoin(tmp, value)));
	}
	free(tmp);
}

void	cd(const char *path, t_list *var_list)
{
	char	*current_pwd;
	char	*new_pwd;
	
	current_pwd = ft_strdup(lst_get_by_key(var_list, "PWD")->value);
	if (chdir(path) != 0)
		perror("bash: cd: a");
	new_pwd = getcwd(NULL, 0);
	if(!new_pwd)
		perror("getcwd()");
	lst_write(var_list, "PWD", new_pwd);
	lst_write(var_list, "OLDPWD", current_pwd);
	system("leaks minishell");
}
