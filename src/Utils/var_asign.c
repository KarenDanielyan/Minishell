/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_asign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:13:16 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/06 01:31:05 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "list.h"
#include <libft.h>

char	**get_key_value(char *assign_word)
{
	char	**split;

	split = (char **)malloc(3 * sizeof(char *));
	split[2] = NULL;
	if (ft_strchr(assign_word, EQUALS))
	{
		split[0] = ft_substr(assign_word, 0, \
			(ft_strchr(assign_word, EQUALS) - assign_word));
		split[1] = ft_strdup(ft_strchr(assign_word, EQUALS) + 1);
	}
	else
	{
		split[0] = ft_strdup(assign_word);
		split[1] = NULL;
	}
	return (split);
}

int	is_assign_word(t_wordl *head)
{
	while (head)
	{
		if (ft_strchr(head->word->value, EQUALS) \
			&& (head->word->flags & (W_SQUOTE | W_DQUOTE)))
			return (1);
		head = head->next;
	}
	return (0);
}
