/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:48:29 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 21:14:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "lex.h"
#include <libft.h>

t_wordl	*wordl_new(t_word *word)
{
	t_wordl	*node;

	node = (t_wordl *)malloc(sizeof(t_wordl));
	node->word = word;
	node->next = NULL;
	return (node);
}

t_wordl	*wordl_last(t_wordl *wordl)
{
	while (wordl->next)
		wordl = wordl->next;
	return (wordl);
}

void	wordl_push_back(t_wordl **wordl, t_word *word)
{
	t_wordl	*new_node;

	if (wordl)
	{
		new_node = wordl_new(word);
		if (*wordl)
			wordl_last(*wordl)->next = new_node;
		else
			*wordl = new_node;
	}
}

void	wordl_push_front(t_wordl **wordl, t_word *word)
{
	t_wordl	*new_node;

	if (wordl)
	{
		new_node = wordl_new(word);
		if (*wordl)
			new_node->next = *wordl;
		*wordl = new_node;
	}
}

void	wordl_clear(t_wordl *wordl)
{
	t_wordl	*tmp;

	while (wordl)
	{
		tmp = wordl->next;
		word_delete(wordl->word);
		free(wordl);
		wordl = tmp;
	}
}
