/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:24:45 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/10 16:25:06 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

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

t_wordl	*wordl_join_free(t_wordl *sublist)
{
	t_word	*word;

	word = wordl_join(sublist);
	wordl_clear(sublist);
	return (wordl_new(word));
}
