/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:56:09 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 23:36:34 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "defines.h"

void	field_splitting(t_node *node, t_list *var_list);
void	tilde_exp(t_node *node, t_list *var_list);
void	param_exp(t_node *node, t_list *var_list);
void	quote_removal(t_node *node);
void	glob_exp(t_node *node);
void	join(t_node *self);

/* Utils */
int		wildcard_match(const char *pattern, const char *string);

void	remove_quotes(t_word *word);

#endif
