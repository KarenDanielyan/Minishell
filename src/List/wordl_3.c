/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:24:45 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/10 17:33:14 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

/**
 * @brief	wordl_sublist() create a sub list that contains
 * 			elements from `from` to `to` elements of the list.
 * 
 * @param from 
 * @param to 
 * @return t_wordl* 
 */
t_wordl	*wordl_sublist(t_wordl *from, t_wordl *to)
{
	t_wordl	*new;

	new = NULL;
	while (1)
	{
		if (new)
			wordl_last(new)->next = wordl_dup_one(from);
		else
			new = wordl_dup_one(from);
		if (from == to)
			break ;
		from = from->next;
	}
	return (new);
}

/**
 * @brief	wordl_join_free() joins the elements from the word list list,
 * 			and return a word list sized one contaning the joined word.
 * 
 * @param list 
 * @return t_wordl* 
 */
t_wordl	*wordl_join_free(t_wordl *list)
{
	t_word	*word;

	word = wordl_join(list);
	wordl_clear(list);
	return (wordl_new(word));
}
