/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:44 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/03 19:28:25 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * 
 * 			History builtin prints on the screen the contents
 * 			of the history file.
 */
void	history(void)
{
	int		i;
	int		fd;
	char	*line;
	char	*filename;

	i = 1;
	line = NULL;
	filename = ft_strjoin(getenv("HOME"), HIST_FILE);
	fd = open(filename, O_RDONLY);
	free(filename);
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
