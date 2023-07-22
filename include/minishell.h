/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:00:51 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/22 14:36:21 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include "list.h"
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <ft_printf.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/**
 * TODO: Implmement error detection and recovery routines.
*/

/* Initialization */
t_control	init(int ac, char **av, char **env);
void		sig_init(void);

/* Get next prompt*/
char		*get_line(t_list *var_list, int fd);

/* Lexical Analysis */
t_token		*lex(char *s, t_list *var_list);

/* Parsing */
void		drop(t_control *ctl, t_node *self);
void		*parse(t_token	*scanner, t_list *var_list);

/* Expansions */
void		expand(t_control *ctl, t_node *self);
void		preprocess(t_control *ctl, t_node *self);

/* Execution */
int			execute(t_control *ctl, t_node *self);

/* Tree Visit Function */
void		visit(t_control *ctl, t_node *self, \
	void (*op)(t_control *ctl, t_node *self));

/* Built-Ins */
int			history(t_wordl *args, t_control *ctl);
int			my_exit(t_wordl *args, t_control *ctl);
int			unset(t_wordl *args, t_control *ctl);
int			export(t_wordl *args, t_control *ctl);
int			cd(t_wordl *args, t_control *ctl);
int			set(t_wordl *cmd, t_control *ctl);
int			echo(t_wordl *cmd, t_control *ctl);
int			env(t_wordl *cmd, t_control *ctl);
int			pwd(t_wordl *cmd, t_control *ctl);

/* Utils */
void		set_ecode(t_control *ctl);
void		print_logo(void);

char		**get_env(t_list *var_list);
char		**get_env_key(t_list	*var_list);
char		**get_key_value(char *assign_word);

int			is_assign_word(t_wordl *head);
int			is_quote(char c, int *flags);
int			is_name(char *str);
int			my_fork(void);

/* Signal */
int			handler(void);

#endif
