/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:15:33 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 23:25:47 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

static int		is_join_required(t_wordl *head);
static t_wordl	*get_joined_word(t_wordl *head);
static int		is_join_required(t_wordl *head);
static t_wordl	*get_joined_word(t_wordl *head);
static t_wordl	*get_sublist(t_wordl *head, t_wordl **next);
static void		get_dimensions(t_wordl *head, t_wordl **from, \
	t_wordl **to, t_wordl **next);
static void		get_dimensions(t_wordl *head, t_wordl **from, \
	t_wordl **to, t_wordl **next);

/**
 * @brief	As in our implementation each word is represented
 * 			in a word list, we have to generate a word from our
 * 			word_list.
 * 			Our word will be in a word_list with size 1,
 * 			unless, our list contains entries generated from,
 * 			filename expansion or field splitting.
*/
void	join(t_node *self)
{
	t_wordl	*new_list;
	t_wordl	*head;

	head = self->value.word;
	if (is_join_required(head))
	{
		new_list = get_joined_word(head);
		wordl_clear(head);
	}
	else
		new_list = head;
	self->value.word = new_list;
}

static int	is_join_required(t_wordl *head)
{
	while (head)
	{
		if (!(head->word->flags & (W_SPLIT | W_FILEEXP)))
			return (1);
		head = head->next;
	}
	return (0);
}

/**
 * @brief	get_joined_word() will return a version of the
 * 			list that has the appropriate fields joined together.
*/
static t_wordl	*get_joined_word(t_wordl *head)
{
	t_wordl	*sub_list;
	t_wordl	*next;
	t_wordl	*new;

	new = NULL;
	next = NULL;
	while (head)
	{
		sub_list = get_sublist(head, &next);
		if (new)
			wordl_last(new)->next = sub_list;
		else
			new = sub_list;
		head = next;
	}
	return (new);
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
	t_wordl	*joined_sublist;
	t_wordl	*sublist;
	t_wordl	*from;
	t_wordl	*to;

	sublist = NULL;
	get_dimensions(head, &from, &to, next);
	joined_sublist = wordl_join_free(wordl_sublist(from, to));
	if (head != from)
		sublist = wordl_sublist(head, wordl_find_prev(head, from));
	if (sublist)
		(wordl_last(sublist))->next = joined_sublist;
	else
		sublist = joined_sublist;
	return (sublist);
}

static void	get_dimensions(t_wordl *head, t_wordl **from, \
	t_wordl **to, t_wordl **next)
{
	t_wordl	*tmp;

	tmp = head;
	while (head && (head->word->flags & (W_SPLIT | W_FILEEXP)))
		head = head->next;
	if (tmp != head)
		*from = wordl_find_prev(tmp, head);
	else
		*from = head;
	while (head && !(head->word->flags & (W_SPLIT | W_FILEEXP)))
		head = head->next;
	*to = head;
	if (head)
		*next = head->next;
	else
		*next = NULL;
}
