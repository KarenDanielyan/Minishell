/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:25:50 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 21:13:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

static t_wordl	*split_and_push(t_wordl **current, t_list *var_list);
static void		set_split_flags(t_wordl *current, t_wordl *replace);
static void		set_values(t_node *node, t_wordl *prev, \
	t_wordl *current, t_wordl *next);

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
		next = current->next;
		if ((current->word->flags & (W_PARMEXP | W_ASSIGNMENT)) == W_PARMEXP \
			&& *(current->word->value))
		{
			prev = wordl_find_prev(node->value.word, current);
			before_replace = current;
			current = split_and_push(&current, var_list);
			set_values(node, prev, current, next);
			if (current && before_replace != current)
				wordl_last(current)->next = next;
		}
		current = next;
	}
}

static void	set_values(t_node *node, t_wordl *prev, \
	t_wordl *current, t_wordl *next)
{
	if (current)
	{
		if (prev)
			prev->next = current;
		else
			node->value.word = current;
	}
	else
	{
		if (prev)
			prev->next = next;
		else
			node->value.word = next;
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
		wordl_push_back(&replace, \
			word_new(*(split + i), (*current)->word->flags));
	set_split_flags(*current, replace);
	(*current)->next = NULL;
	wordl_clear(*current);
	free_2d(split);
	return (replace);
}

static void	set_split_flags(t_wordl *current, t_wordl *replace)
{
	t_wordl	*tmp;
	t_wordl	*prev;
	char	*cur_val;
	char	*split_val;

	tmp = replace;
	cur_val = current->word->value;
	while (tmp)
	{
		split_val = tmp->word->value;
		prev = wordl_find_prev(replace, tmp);
		if (!prev)
		{
			if (*cur_val == *split_val)
				tmp->word->flags = tmp->word->flags | W_JOIN;
		}
		if (!(tmp->next))
		{
			if (cur_val[ft_strlen(cur_val) - 1] \
				== split_val[ft_strlen(split_val) - 1])
				tmp->word->flags = tmp->word->flags | W_JOIN;
		}
		tmp->word->flags = tmp->word->flags | W_SPLIT;
		tmp = tmp->next;
	}
}
