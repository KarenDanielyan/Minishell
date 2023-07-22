/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:24:45 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/21 22:51:07 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

/**
 * @brief	wordl_sublist() create a sub list that contains
 * 			elements from `from` to `to` elements of the list.
 * 
 * 			NOTE: if word is to not be joined as indicated in
 * 			W_JOIN flag, to will not be part of the list.
 * 
 * @param from 
 * @param to 
 * @return t_wordl* 
 */
t_wordl	*wordl_sublist(t_wordl *from, t_wordl *to)
{
	t_wordl	*new;

	new = NULL;
	if (from)
	{
		while (1)
		{
			if (new)
				wordl_last(new)->next = wordl_dup_one(from);
			else
				new = wordl_dup_one(from);
			if (!to || to->word->flags & W_JOIN)
			{
				if (from == to)
					break ;
			}
			else if (!from || from->next == to)
				break ;
			from = from->next;
		}
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
	t_wordl	*new;

	new = NULL;
	if (list)
	{
		word = wordl_join(list);
		wordl_clear(list);
		new = wordl_new(word);
	}
	return (new);
}

void	wordl_pop(t_wordl **head, t_wordl *to_pop)
{
	t_wordl	*prev;

	if (to_pop)
	{
		prev = wordl_find_prev(*head, to_pop);
		if (prev)
			prev->next = to_pop->next;
		if (*head == to_pop)
			*head = to_pop->next;
		word_delete(to_pop->word);
		free(to_pop);
	}
}

char	**wordl_to_array(t_wordl *word)
{
	int		len;
	char	**arr;
	char	**tmp;

	len = wordl_size(word);
	arr = (char **)malloc((len + 1) * sizeof(char *));
	tmp = arr;
	while (word)
	{
		*tmp = ft_strdup(word->word->value);
		tmp ++;
		word = word->next;
	}
	*tmp = NULL;
	return (arr);
}
