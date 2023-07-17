/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:02:25 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/18 00:47:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

/**
 * @brief	wordl_size() returns the number of elements
 * 			inside the word list.
 * 
 * @param head	Pointer to the first element of the list.
 */
int	wordl_size(t_wordl *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i ++;
	}
	return (i);
}

/**
 * @brief	wordl_join() allocates and returns a word,
 * 			which is composed of the words contained inside
 * 			the word list.
*/
t_word	*wordl_join(t_wordl *wordl)
{
	t_word	*word;
	char	*val;
	int		flags;

	val = NULL;
	flags = 0;
	while (wordl)
	{
		val = ft_strjoin_free(val, wordl->word->value);
		flags = flags | wordl->word->flags;
		wordl = wordl->next;
	}
	word = word_new(val, flags);
	free(val);
	return (word);
}

/**
 * @brief	wordl_fing_prev() return a previous node of the current node.
 * 			if the current node if the head of the list,
 * 			It will return NULL.
 * 
 * @param head		Pointer to the first element of a list.
 * @param current	The element which previous element we want to find.
 * @return t_wordl* 
 */
t_wordl	*wordl_find_prev(t_wordl *head, t_wordl *current)
{
	while (head && head->next != current)
		head = head->next;
	return (head);
}

/**
 * @brief	wordl_dup_one() duplicates word list node node, 
 * 			without the references to the next node in the list.
 * 
 * @param node 
 * @return t_wordl* 
 */
t_wordl	*wordl_dup_one(t_wordl *node)
{
	t_wordl	*new;

	new = NULL;
	if (node)
		new = wordl_new(word_new(node->word->value, node->word->flags));
	return (new);
}

/**
 * @brief	wordl_dup() duplicates word list pointed by head, and
 * 			returns it. If malloc fails, it will return (NULL);
 * 
 * @param head 
 * @return t_wordl* 
 */
t_wordl	*wordl_dup(t_wordl *head)
{
	t_wordl	*new;

	new = NULL;
	while (head)
	{
		if (new)
			wordl_last(new)->next = wordl_dup_one(head);
		else
			new = wordl_dup_one(head);
		head = head ->next;
	}
	return (new);
}
