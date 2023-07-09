/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:25:50 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/10 01:22:55 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

static t_wordl	*split_and_push(t_wordl **current, t_list *var_list);

void	field_splitting(t_node *node, t_list *var_list)
{
	t_wordl	*prev;
	t_wordl	*current;
	t_wordl	*before_replace;
	t_wordl	*next;

	current = node->value.word;
	prev = NULL;
	while (current)
	{
		prev = wordl_find_prev(node->value.word, current);
		next = current->next;
		before_replace = current;
		current = split_and_push(&current, var_list);
		if (prev)
			prev->next = current;
		else
			node->value.word = current;
		if (before_replace != current)
		{
			before_replace = wordl_last(current);
			before_replace->next = next;
		}
		current = next;
	}
}

static t_wordl	*split_and_push(t_wordl **current, t_list *var_list)
{
	t_wordl	*replace;
	t_list	*ifs;
	char	**split;
	int		i;

	replace = NULL;
	ifs = lst_get_by_key(var_list, IFS);
	if (((*current)->word->flags & (W_SQUOTE | W_DQUOTE))
		|| (ifs && ifs->value == NULL))
		return (*current);
	if (ifs == NULL)
		split = ft_split_2((*current)->word->value, IFS_VAL);
	else
		split = ft_split_2((*current)->word->value, ifs->value);
	i = -1;
	while (split[++i])
	{
		wordl_push_back(&replace, \
			word_new(*(split + i), ((*current)->word->flags | W_SPLIT)));
	}
	(*current)->next = NULL;
	wordl_clear(*current);
	free_2d(split);
	return (replace);
}
