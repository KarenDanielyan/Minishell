/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:15:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/28 17:24:31 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

#include "defines.h"

/**
 * @brief Variable list structure.
 * 
 * @param type		Determines the scope of the variable.
 * @param joined	string of key-value pair joined with an '='. Ex: 'var=foo'
 * @param key		Variable name.
 * @param value		Value of the varaible.
 * @param prev		Previous variable the variable list.
 * @param next		Next variable in the variable list.
 */
typedef struct s_list
{
	t_scope	type;
	char	*joined;
	char	*key;
	char	*value;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_list;

#endif