/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:10:44 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 14:35:19 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "defines.h"
# include "list.h"

t_control	init(int ac, char **av, char **env);

t_list		*env_init(char **env);

t_flist		*builtin_init(void);

void		sig_init(void);
void		mode_init(int ac, char **av);

#endif