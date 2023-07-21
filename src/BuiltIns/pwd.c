/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:01:08 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 17:51:09 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_wordl *cmd, t_control *ctl)
{
	char	*pwd;

	(void)cmd;
	(void)ctl;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (EXIT_SUCCESS);
	}
	perror(EPERROR);
	return (EXIT_FAILURE);
}
