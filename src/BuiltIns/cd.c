/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:29:40 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 17:51:03 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_values(t_list *var_list, char *new_pwd, char *current_pwd);
static int	cd_default(t_list *path, t_control *ctl);
static char	*my_get_cwd(void);

/**
 * @brief 
 * 
 * @param key 
 * @param value Use strdup before passing the argument.
 */
int	cd(t_wordl *args, t_control *ctl)
{
	t_wordl	*path;
	char	*current_pwd;
	char	*new_pwd;

	new_pwd = NULL;
	current_pwd = NULL;
	path = args->next;
	if (!path)
	{
		if (cd_default(lst_get_by_key(ctl->var_list, "HOME"), ctl))
			return (EXIT_FAILURE);
	}
	if (lst_get_by_key(ctl->var_list, "PWD"))
		current_pwd = ft_strdup(lst_get_by_key(ctl->var_list, "PWD")->value);
	if (chdir(path->word->value) != 0)
	{
		perror("minishell: cd");
		lst_set(ctl->var_list, ECODE, FAIL);
		return (EXIT_FAILURE);
	}
	new_pwd = my_get_cwd();
	if (!new_pwd)
		return (EXIT_FAILURE);
	set_values(ctl->var_list, new_pwd, current_pwd);
	return (EXIT_SUCCESS);
}

static void	set_values(t_list *var_list, char *new_pwd, char *current_pwd)
{
	lst_set(var_list, "PWD", new_pwd);
	lst_set(var_list, "OLDPWD", current_pwd);
	free(new_pwd);
	free(current_pwd);
}

static int	cd_default(t_list *path, t_control *ctl)
{
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, "bash: cd: HOME not set\n");
		lst_set(ctl->var_list, ECODE, "1");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	*my_get_cwd(void)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		perror(EPERROR);
	return (new_pwd);
}
