/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:02:25 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/08 19:18:37 by dohanyan         ###   ########.fr       */
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
