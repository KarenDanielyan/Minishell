/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:25:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 20:09:26 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(t_control *ctl, int fd)
{
	char	*str;

	str = readline(lst_get_by_key(ctl->var_list, "PS1")->value);
	if (!str)
	{
		write (2, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	if (!(*str))
	{
		free(str);
		return (NULL);
	}
	add_history(str);
	ft_putendl_fd(str, fd);
	set_ecode(ctl, FALSE);
	return (str);
}
