/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:02:25 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/10 14:05:46 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

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
 * @brief	wordl_join() allocates and return a word,
 * 			this is composed of the words contained inside,
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

t_wordl	*wordl_find_prev(t_wordl *head, t_wordl *current)
{
	if (head)
	{
		while (head && head->next != current)
			head = head->next;
	}
	return (head);
}

t_wordl	*wordl_dup_one(t_wordl *node)
{
	t_wordl	*new;

	new = NULL;
	if (node)
		new = wordl_new(word_new(node->word->value, node->word->flags));
	return (new);
}

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