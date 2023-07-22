/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:24:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/22 19:05:12 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>

static void	here_doc(t_wordl *word, int out_fd, t_control *ctl);
static void	print_ps2(t_control *ctl);

int	parse_heredoc(t_wordl *word, t_control *ctl)
{
	int		in_fd;
	int		out_fd;
	int		pip[2];
	
	pip[0] = -42;
	out_fd = open(HERE_FILE, O_RDWR | O_CREAT | O_APPEND, 0666);
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
	if (in_fd < 0)
		perror("heredoc");
	close(out_fd);
	return(in_fd);
}

static void	here_doc(t_wordl *word, int out_fd, t_control *ctl)
{
	char	*line;
	char	*tmp;
	int		to_expand;
	t_word	*for_exit;

	to_expand = TRUE;
	for_exit = wordl_join(word);
	for_exit->value = ft_strjoin_free(for_exit->value, "\n");
	if (for_exit->flags & (W_SQUOTE | W_DQUOTE))
		to_expand = FALSE;
	while (1)
	{
		print_ps2(ctl);
		tmp = get_next_line(STDIN_FILENO);
		if (tmp == NULL || ft_strcmp(tmp, for_exit->value) == 0)
			break ;
		if (to_expand)
			line = parmexp(tmp, ctl);
		ft_putstr_fd(line, out_fd);
		free(line);
		free(tmp);
	}
	if (tmp)
		free(tmp);
	word_delete(for_exit);
}

static void	print_ps2(t_control *ctl)
{
	t_list	*ps2;

	ps2 = lst_get_by_key(ctl->var_list, "PS2");
	if (ps2 && ps2->value)
		ft_dprintf(STDERR_FILENO, "%s", ps2->value);
}