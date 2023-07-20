/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:56:09 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 13:21:12 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "defines.h"
# include "list.h"

void	tilde_exp(t_node *node, t_list *var_list);
void	param_exp(t_node *node, t_list *var_list);
void	field_splitting(t_node *node, t_list *var_list);
void	glob_exp(t_node *node);
void	quote_removal(t_node *node);
void	join(t_node *self);

#endif