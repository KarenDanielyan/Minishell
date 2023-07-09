/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:29:40 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/09 21:53:53 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param key 
 * @param value Use strdup before passing the argument.
 */

static void	set_values(t_list *var_list, char *new_pwd, char *current_pwd);

void	cd(t_wordl *wordl, t_list *var_list)
{
	char	*path;
	char	*current_pwd;
	char	*new_pwd;

	path = NULL;
	new_pwd = NULL;
	current_pwd = NULL;
	if (wordl->next)
		path = wordl->next->word->value;
	if (!lst_get_by_key(var_list, "HOME"))
	{
		ft_dprintf(STDERR_FILENO, "bash: cd: HOME not set\n");
		lst_set(var_list, ECODE, "1");
		return ;
	}
	if (!path)
		path = lst_get_by_key(var_list, "HOME")->value;
	if (lst_get_by_key(var_list, "PWD"))
		current_pwd = ft_strdup(lst_get_by_key(var_list, "PWD")->value);
	if (chdir(path) != 0)
	{
		perror("Minishell: cd");
		lst_set(var_list, ECODE, "1");
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		perror("getcwd()");
	set_values(var_list, new_pwd, current_pwd);
}

static void	set_values(t_list *var_list, char *new_pwd, char *current_pwd)
{
	lst_set(var_list, "PWD", new_pwd);
	lst_set(var_list, "OLDPWD", current_pwd);
	free(new_pwd);
	free(current_pwd);
}
