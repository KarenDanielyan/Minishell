/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:16:38 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/24 13:41:04 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

#include <stdlib.h>

typedef struct s_btree
{
	void			*content;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;



#endif