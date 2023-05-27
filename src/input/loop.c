/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:57:14 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/27 17:49:02 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief		showing history
 * 
 * 	this function again opne history file and when
 * 	we writing "history" word he show us all comandin inside it
 * 
 */
void	history(void)
{
	int		i;
	int		fd;
	char	*line;
	char	*filename;

	i = 1;
	line = NULL;
	filename = ft_strjoin(getenv("HOME"), "/.minishell_history");
	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf ("%d	%s", i++, line);
		free(line);
		line = NULL;
	}
	close(fd);
}

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
			if (ft_strcmp(str, "history") == 0)
				history();
		}
	}
}
