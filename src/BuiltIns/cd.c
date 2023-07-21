/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:29:40 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 02:17:34 by dohanyan         ###   ########.fr       */
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

void	cd(t_wordl *args, t_control *ctl)
{
	char	*path;
	char	*current_pwd;
	char	*new_pwd;

	path = NULL;
	new_pwd = NULL;
	current_pwd = NULL;
	if (args->next)
		path = args->next->word->value;
	if (!lst_get_by_key(ctl->var_list, "HOME"))
	{
		ft_dprintf(STDERR_FILENO, "bash: cd: HOME not set\n");
		lst_set(ctl->var_list, SHELL, ECODE, FAIL);
		return ;
	}
	if (!path)
		path = lst_get_by_key(ctl->var_list, "HOME")->value;
	if (lst_get_by_key(ctl->var_list, "PWD"))
		current_pwd = ft_strdup(lst_get_by_key(ctl->var_list, "PWD")->value);
	if (chdir(path) != 0)
	{
		perror("Minishell: cd");
		lst_set(ctl->var_list, SHELL, ECODE, FAIL);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		perror("getcwd()");
	set_values(ctl->var_list, new_pwd, current_pwd);
}

static void	set_values(t_list *var_list, char *new_pwd, char *current_pwd)
{
	lst_set(var_list, LOCAL, "PWD", new_pwd);
	lst_set(var_list, EXPORT, "OLDPWD", current_pwd);
	free(new_pwd);
	free(current_pwd);
}
