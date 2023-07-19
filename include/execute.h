/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:17:41 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/19 15:59:05 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <sys/wait.h>
# include "defines.h"
# include "list.h"

void	execute(t_control *ctl, t_node *self);

void	execute_pipeline(t_control *ctl, t_node *self);
void	execute_scommand(t_control *ctl, t_node *self);
void	execute_ccommand(t_control *ctl, t_node *self);
void	execute_command(t_control *ctl, t_node *self);
void	execute_prefix(t_control *ctl, t_node *self);
void	execute_suffix(t_control *ctl, t_node *self);
void	execute_list(t_control *ctl, t_node *self);
void	execute_io(t_control *ctl, t_node *self);

/* Utils */
char	*get_file_path(char **path, char *file);
char	**get_path(t_list *var_list);

int		is_assignment(t_word *word);

#endif
