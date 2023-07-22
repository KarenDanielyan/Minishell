/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:24:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/22 16:17:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>

static void	here_doc(t_wordl *word, int out_fd, t_control *ctl);

int	parse_heredoc(t_wordl *word, t_control *ctl)
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
	here_doc(word, out_fd, ctl);
	if (pip[0] > 0)
		in_fd = pip[0];
	else
		in_fd = open(HERE_FILE, O_RDONLY);
	close(out_fd);
	return(in_fd);
}

static void	here_doc(t_wordl *word, int out_fd, t_control *ctl)
{
	char	*line;
	int		to_expand;
	t_word	*for_exit;

	to_expand = TRUE;
	for_exit = wordl_join(word);
	for_exit->value = ft_strjoin_free(for_exit->value, "\n");
	if (for_exit->flags & (W_SQUOTE | W_DQUOTE))
		to_expand = FALSE;
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strcmp(line, for_exit->value) == 0)
			break ;
		if (to_expand)
			line = parmexp(line, ctl);
		ft_putstr_fd(line, out_fd);
		free(line);
	}
}