/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:25:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/30 18:31:08 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	*get_line(t_control *ctl, int fd)
{
	t_list	*ps1;
	char	*str;

	ps1 = lst_get_by_key(ctl->var_list, "PS1");
	if (ps1 && ps1->value)
		str = ps1->value;
	else
		str = NULL;
	str = readline(str);
	if (!str)
	{
		write (2, "exit\n", 5);
		exit(ft_atoi(lst_get_by_key(ctl->var_list, ECODE)->value));
	}
	if (!(*str))
	{
		free(str);
		return (NULL);
	}
	add_history(str);
	ft_putendl_fd(str, fd);
	return (str);
}
