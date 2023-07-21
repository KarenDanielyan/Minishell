/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:24:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 23:37:00 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>

static void	here_doc(t_wordl *word, int out_fd);

int	parce_heredoc(t_wordl *word)
{
	int		in_fd;
	int		out_fd;
	int		pip[2];
	
	pip[0] = -42;
	out_fd = open(HERE_FILE, O_CREAT | O_TRUNC | O_APPEND, 0666);
	if (out_fd < 0)
	{
		pipe(pip);
		out_fd = pip[1];
	}
	here_doc(word, out_fd);
	if (pip[0] > 0)
		in_fd = pip[0];
	else
		in_fd = open(HERE_FILE, O_RDONLY);
	close(out_fd);
	return(in_fd);
}

static void	here_doc(t_wordl *word, int out_fd)
{
	int		i;
	char	*for_exit;
	char	*line;

	i = 0;
	for_exit = word->next->word->value;
	for_exit = ft_strjoin_free(for_exit, "\n");
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strcmp(line, for_exit) == 0)
			break ;
		write (out_fd, line, ft_strlen(line));
		free(line);
	}
}