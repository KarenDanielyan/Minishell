/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:15:33 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/10 20:12:48 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

static t_wordl	*get_sublist(t_wordl *head, t_wordl **next);

/**
 * @brief	As in our implementation each word is represented
 * 			in a word list, we have to generate a word from our
 * 			word_list.
 * 			Our word will be in a word_list with size 1,
 * 			unless, our list contains entries generated from,
 * 			filename expansion or field splitting.
*/
t_wordl	*make_word(t_wordl *head)
{
	t_wordl	*tmp;
	t_wordl	*next;
	t_wordl	*sub_list;
	t_wordl	*new_list;

	tmp = head;
	next = NULL;
	new_list = NULL;
	while (tmp)
	{
		sub_list = get_sublist(head, &next);
		if (new_list)
			wordl_last(new_list)->next = sub_list;
		else
			new_list = sub_list;
		tmp = next;
	}
	wordl_clear(head);
	return (new_list);
}

/**
 * @brief	get_sublist() will find from/until where we should start joining,
 * 			It will then create a list that contains non-joined nodes with 
 * 			joinded node at the end.
 * 
 * @param head 
 * @param next 
 * @return t_wordl* 
 */
static t_wordl	*get_sublist(t_wordl *head, t_wordl **next)
{
	t_wordl	*from;
	t_wordl	*tmp;
	t_wordl	*to;

	tmp = head;
	while (head && (head->word->flags & (W_SPLIT | W_FILEEXP)))
		head = head->next;
	from = wordl_find_prev(tmp, head);
	while (head && !(head->word->flags & (W_SPLIT | W_FILEEXP)))
		head = head->next;
	to = head;
	if (head)
		*next = head->next;
	else
		*next = NULL;
	if (tmp != from)
	{
		tmp = wordl_sublist(tmp, wordl_find_prev(tmp, from));
		(wordl_last(tmp))->next = wordl_join_free(wordl_sublist(from, to));
	}
	else
		tmp = wordl_join_free(wordl_sublist(from, to));
	return (tmp);
}
