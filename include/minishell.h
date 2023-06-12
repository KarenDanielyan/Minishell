/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:00:51 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/12 14:27:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"
# include "tree.h"
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Initialization */
void	sig_init(void);
t_list	*env_init(char **env);
void	mode_init(int ac, char **av);

/* Built-Ins */
void	history(t_list *var_list);
void	pwd(void);
void	cd(const char *path, t_list *env);
void	env(t_list *env);
void	unset(t_list **var_l, char *key);

/* Utils */
void	print_logo(void);

char	**get_env(t_list *var_list);

#endif