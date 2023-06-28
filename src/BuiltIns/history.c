/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:44 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/27 20:59:49 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * 
 * 			History builtin prints on the screen the contents
 * 			of the history file.
 */
void	history(t_wordl *wordl, t_list *var_list)
{
	int		i;
	int		fd;
	char	*line;
	char	*filename;

	i = 1;
	line = NULL;
	if (wordl_size(wordl) > 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: history: %s numeric argument required\n",
			wordl->next->word->value);
		return ;
	}
	filename = lst_get_by_key(var_list, "HISTFILE")->value;
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
