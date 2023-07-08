/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:00:51 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/08 19:49:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include "list.h"
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
void	sig_init(void);
t_list	*env_init(char **env);
void	mode_init(int ac, char **av);

/* Get next prompt*/
char	*get_line(t_list *var_list, int fd);

/* Lexical Analysis */
t_token	*lex(char *s);

/* Parsing */
void	drop(t_control *ctl, t_node *self);
void	*parse(t_token	*scanner, t_list *var_list);

/* Expansions */
void	expand(t_control *ctl, t_node *self);

/* Tree Visit Function */
void	visit(t_control *ctl, t_node *self, \
	void (*op)(t_control *ctl, t_node *self));

/* Built-Ins */
void	history(t_wordl *wordl, t_list *var_list);
void	pwd(void);
void	cd(t_wordl *wordl, t_list *var_list);
void	env(t_list *env);
void	unset(t_list **var_list, t_wordl *wordl);
void	my_exit(t_list *var_list, t_wordl *wordl);
void	echo(t_wordl *wordl);
void	export(t_list *var_list, t_wordl *args);

/* Utils */
void	print_logo(void);

char	**get_env(t_list *var_list);
char	**get_env_key(t_list	*var_list);
char	**get_key_value(char *assign_word);

int		is_assign_word(t_wordl *head);
int		is_quote(char c, int *flags);
int		is_name(char *str);

/* Signal */
int		handler(void);

#endif
