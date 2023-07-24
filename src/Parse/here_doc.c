/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:24:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/24 17:12:43 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expand.h"
#include <sys/wait.h>
#include <libft.h>
#include <stdio.h>

static void		print_ps2(t_control *ctl);
static void		here_doc(t_control *ctl, t_word *limiter, \
	int expand, int write_fd);

static t_word	*setup_hdoc(t_pipe *fifo, t_wordl *word, int *to_expand);

int	parse_heredoc(t_wordl *word, t_control *ctl)
{
	t_pipe	fifo;
	t_word	*limiter;
	int		to_expand;
	int		pid;

	limiter = setup_hdoc(&fifo, word, &to_expand);
	pid = my_fork(ctl);
	if (pid < 0)
		return (-1);
	if (pid == 0)
		here_doc(limiter, fifo.out, ctl);
	waitpid(pid, ctl->estat, 0);
	if (WIFEXITED(*(ctl->estat)))
	{
		if (fifo.in < 0)
			fifo.in = open(HERE_FILE, O_RDONLY);
		if (fifo.in < 0)
			perror(EPERROR);
	}
	else
		fifo.in = -1;
	return (fifo.in);
}

static void	here_doc(t_control *ctl, t_word *limiter, int expand, int write_fd)
{
	char	*line;
	char	*tmp;

	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	line = NULL;
	tmp = NULL;
	while (1)
	{
		print_ps2(ctl);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strcmp(line, limiter->value) == 0)
			break ;
		tmp = line;
		if (expand)
			line = parmexp(tmp, ctl);
		else
			line = ft_strdup(tmp);
		ft_putstr_fd(line, out_fd);
		free(tmp);
		free(line);
	}
	exit(EXIT_SUCCESS);
}

static void	print_ps2(t_control *ctl)
{
	t_list	*ps2;

	ps2 = lst_get_by_key(ctl->var_list, "PS2");
	if (ps2 && ps2->value)
		ft_dprintf(STDERR_FILENO, "%s", ps2->value);
}

static t_word	*setup_hdoc(t_pipe *fifo, t_wordl *word, int *to_expand)
{
	t_word	*limiter;
	int		write_fd;
	int		pip[2];

	write_fd = open(HERE_FILE, O_RDWR | O_CREAT | O_APPEND, 0666);
	fifo->in = -42;
	if (write_fd < 0)
	{
		pipe(pip);
		fifo->in = pip[0];
		fifo->out = pip[1];
	}
	limiter = wordl_join(word);
	remove_quotes(limiter);
	(limiter)->value = ft_strjoin_free(limiter->value, "\n");
	if (limiter->flags & (W_SQUOTE | W_DQUOTE))
		*to_expand = FALSE;
	else
		*to_expand = TRUE;
}
