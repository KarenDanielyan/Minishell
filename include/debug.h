/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:50:19 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/30 16:34:17 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/*
*	NOTE: Files and functions associated with debug features are not
*	the part of the project, and cannot be used during evaluation.
*	This functions were implemented out of convinience, to help us
*	find problems easier during production.
*/

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include "minishell.h"
# include "defines.h"
# include "lex.h"
# include "list.h"
# include "tree.h"

void	print_tokens(t_tokl	*token_list);

/* Utils */
char	*get_type(int type);

# endif