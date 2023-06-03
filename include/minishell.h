/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:00:51 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/02 21:33:28 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"
# include "tree.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>

void	history(void);

t_list	*env_init(char **env);
void	pwd(void);
void cd(const char *path,t_list *env);
void	env(t_list *env);

/* Utils */
char	**get_env(t_list *var_list);

#endif