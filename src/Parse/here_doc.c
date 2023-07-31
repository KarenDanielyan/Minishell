/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:24:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/01 03:20:54 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"
#include "parser.h"
#include "expand.h"
#include <sys/wait.h>
#include <libft.h>
#include <termios.h>

static char		*get_here_line(t_list *ps2);

static void		cleanup(t_word *limiter, t_pipe *fifo);
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
	if (limiter == NULL)
		return (-1);
	pid = my_fork(ctl);
	if (pid < 0)
	{
		cleanup(limiter, &fifo);
		return (-1);
	}
	if (pid == 0)
		here_doc(ctl, limiter, to_expand, fifo);
	waitpid(pid, ctl->estat, 0);
	if (WIFSIGNALED(*(ctl->estat)))
	{
		if (WTERMSIG(*(ctl->estat)) == SIGINT)
			write(1, "\n", 1);
		fifo.in = -1;
	}
	cleanup(limiter, &fifo);
	return (fifo.in);
}

static void	cleanup(t_word *limiter, t_pipe *fifo)
{
	set_attr(1);
	word_delete(limiter);
	close(fifo->out);
}

static void	here_doc(t_control *ctl, t_word *limiter, int expand, t_pipe fifo)
{
	char	*line;
	char	*tmp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	tmp = NULL;
	while (1)
	{
		line = get_here_line(lst_get_by_key(ctl->var_list, "PS2"));
		if (line == NULL || ft_strcmp(line, limiter->value) == 0)
			break ;
		tmp = line;
		if (expand)
			line = parmexp(tmp, ctl);
		else
		{
			line = ft_strdup(tmp);
			ft_strappend(&tmp, NEWLINE);
		}
		ft_putstr_fd(line, fifo.out);
		free(tmp);
		free(line);
	}
	close(fifo.in);
	close(fifo.out);
	exit(EXIT_SUCCESS);
}

static char	*get_here_line(t_list *ps2)
{
	const char	*arg;

	if (ps2)
		arg = ps2->value;
	else
		arg = NULL;
	return (readline(arg));
}

static t_word	*setup_hdoc(t_pipe *fifo, t_wordl *word, int *to_expand)
{
	t_word	*limiter;
	int		pip[2];

	set_attr(0);
	if (pipe(pip) < 0)
	{
		ft_dprintf(STDERR_FILENO, "%s%s: %s\n", EPERROR, \
			"here_doc:", strerror(errno));
		return (NULL);
	}
	fifo->in = pip[0];
	fifo->out = pip[1];
	limiter = wordl_join(word);
	remove_quotes(limiter);
	if (limiter->flags & (W_SQUOTE | W_DQUOTE))
		*to_expand = FALSE;
	else
		*to_expand = TRUE;
	return (limiter);
}
