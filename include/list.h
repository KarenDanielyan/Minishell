/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:15:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/30 15:59:15 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "defines.h"

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
	t_scope			type;
	char			*joined;
	char			*key;
	char			*value;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

/* API functions */

int		lst_size(t_list *lst);

t_list	*lst_last(t_list *lst);
t_list	*get_node(t_list *lst, int loc);
t_list	*lst_new(int type, char *key_val);

void	lst_clear(t_list **lst, void (*del)(void *));
void	lst_push_front(t_list **lst, t_list *new);
void	lst_push_back(t_list **lst, t_list *new);

#endif