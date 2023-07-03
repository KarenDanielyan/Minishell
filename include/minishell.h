/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:00:51 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/03 22:34:24 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lex.h"
# include "list.h"
# include "tree.h"
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <ft_printf.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Initialization */
void	sig_init(void);
t_list	*env_init(char **env);
void	mode_init(int ac, char **av);

/* Built-Ins */
void	history(t_wordl *wordl,t_list *var_list);
void	pwd(void);
void	cd(t_wordl *wordl, t_list *var_list);
void	env(t_list *env);
void	unset(t_list **var_list, t_wordl *wordl);
void	my_exit(t_list *var_list, t_wordl *wordl);
void	echo(t_wordl *wordl);
void	export(t_list *var_list, t_wordl* args);

/* Utils */
void	print_logo(void);

char	**get_env(t_list *var_list);
char	**get_env_key(t_list	*var_list);

int	is_quote(char c, int *flags);
int	is_name(char *str);

/* Signal */
int	handler(void);

#endif
