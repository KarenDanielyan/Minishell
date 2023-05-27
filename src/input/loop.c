/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:57:14 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/27 16:28:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief		Readline while loop
 * 
 * @param fd	fd for history file
 * 
 */
void	true_loop(void)
{
	int		fd;
	char	*str;
	char	*filename;


	filename = ft_strjoin(getenv("HOME"), "/.minishell_history");
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	free(filename);
	while (1)
	{
		str = readline("minishell-3.2$ ");
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			ft_putendl_fd(str, fd);
		}
	}
}
