/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:56:09 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/08 15:49:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "defines.h"

void	tilde_expand(t_node *node);
void	param_expand(t_node *node);
void	field_splitting(t_node *node, t_list *var_list);
void	glob_expand(t_node *node);
void	quote_removal(t_node *node);

#endif