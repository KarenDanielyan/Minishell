/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:24:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/25 16:01:35 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"
#include "parser.h"
#include "expand.h"
#include <sys/wait.h>
#include <libft.h>
#include <termios.h>

static void		cleanup(t_word *limiter, t_pipe fifo);
static void		here_doc(t_control *ctl, t_word *limiter, \
	int expand, t_pipe fifo);

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
		here_doc(ctl, limiter, to_expand, fifo);
	waitpid(pid, ctl->estat, 0);
	if (WIFSIGNALED(*(ctl->estat)))
	{
		if (WTERMSIG(*(ctl->estat)))
			write(1, "\n", 1);
		return (-1);
	}
	cleanup(limiter, fifo);
	return (fifo.in);
}

static void	cleanup(t_word *limiter, t_pipe fifo)
{
	if (fifo.in < 0)
		fifo.in = open(HERE_FILE, O_RDONLY);
	if (fifo.in < 0)
		perror(EPERROR);
	set_attr(RESET);
	word_delete(limiter);
	close(fifo.out);
}

static void	here_doc(t_control *ctl, t_word *limiter, int expand, t_pipe fifo)
{
	char	*line;
	char	*tmp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	set_attr(SET);
	tmp = NULL;
	while (1)
	{
		shell_print(ctl, "PS2");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strcmp(line, limiter->value) == 0)
			break ;
		tmp = line;
		if (expand)
			line = parmexp(tmp, ctl);
		else
			line = ft_strdup(tmp);
		ft_putstr_fd(line, fifo.out);
		free(tmp);
		free(line);
	}
	close(fifo.in);
	close(fifo.out);
	exit(EXIT_SUCCESS);
}

static t_word	*setup_hdoc(t_pipe *fifo, t_wordl *word, int *to_expand)
{
	t_word	*limiter;
	int		pip[2];

	fifo->out = open(HERE_FILE, O_RDWR | O_CREAT | O_APPEND, 0666);
	fifo->in = -42;
	if (fifo->out < 0)
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
	return (limiter);
}
