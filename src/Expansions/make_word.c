/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:15:33 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/10 03:34:21 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

/**
 * @brief	As in our implementation each word is represented
 * 			in a word list, we have to generate a word from our
 * 			word_list.
 * 			Our word will be in a word_list with size 1,
 * 			unless, our list contains entries generated from,
 * 			filename expansion or field splitting.
*/
t_wordl	*make_word(t_wordl *list)
{
	t_wordl	*new;
	t_wordl	*tmp;
	t_wordl	*from;
	t_wordl	*to;

	tmp = list;
	new = NULL;
	while (tmp)
	{
		while (tmp && (tmp->word->flags & (W_FILEEXP | W_SPLIT)))
			tmp = tmp->next;
		from = tmp;
		while (tmp && !(tmp->word->flags & (W_FILEEXP | W_SPLIT)))
			tmp = tmp->next;
		to = tmp;
		if (new)
			wordl_last(new)->next = wordl_sublist(from, to);
		else
			new = wordl_sublist(from, to);
		tmp = tmp->next;
	}
	return (new);
}

t_wordl	*wordl_sublist(t_wordl *from, t_wordl *to)
{
	t_wordl	*new;
	t_word	*word;

	new = NULL;
	while (from != to)
	{
		if (new)
			wordl_last(new)->next = wordl_dup_one(from);
		else
			new = wordl_dup_one(from);
		from = from->next;
	}
	word = wordl_join(new);
	new = wordl_new(word);
	return (new);
}
