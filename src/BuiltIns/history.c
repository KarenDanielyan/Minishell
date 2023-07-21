/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:44 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/21 18:50:42 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lex.h"

/**
 * @brief
 * 
 * 			History builtin prints on the screen the contents
 * 			of the history file.
 */
int	history(t_wordl *args, t_control *ctl)
{
	int		i;
	int		fd;
	char	*line;
	char	*filename;

	i = 1;
	line = NULL;
	if (wordl_size(args) > 1)
		ft_dprintf(STDERR_FILENO, NOTE_HIST);
	else
	{
		filename = lst_get_by_key(ctl->var_list, "HISTFILE")->value;
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
	return (EXIT_SUCCESS);
}
