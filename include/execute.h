/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:17:41 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/31 11:48:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <sys/wait.h>
# include "defines.h"
# include "list.h"

int		execute(t_control *ctl, t_node *self);

void	execute_pipeline(t_control *ctl, t_node *self);
void	execute_scommand(t_control *ctl, t_node *self);
void	execute_ccommand(t_control *ctl, t_node *self);
void	execute_command(t_control *ctl, t_node *self);
void	execute_list(t_control *ctl, t_node *self);

int		execute_prefix(t_control *ctl, t_node *self);
int		execute_suffix(t_control *ctl, t_node *self);
int		execute_io(t_control *ctl, t_node *self);

/* Utils */
char	*cmd_search(t_wordl *cmd, t_list *var_list, int *flags);

void	handle_builtin(t_control *ctl, t_node *self, t_flist *builtin);
void	execute_and_check(char *cmd, char **args, char **env, int cmd_flags);
void	handle_command(t_control *ctl, t_node *self);

int		is_assignment(t_wordl *wordl);

/* Op for visit function */
void	close_fifo(t_control *ctl, t_node *self);

#endif
