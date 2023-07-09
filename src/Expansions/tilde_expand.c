/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:24:49 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/09 15:35:43 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

/**
 * @brief	tilde_expand() performs tilde-expansion on the word.
 * 			This is overly simplified version of tilde expansion,
 * 			as most of the functions needed to properly implement
 * 			this feature are forbidden.
 * 			In our version, we only look in duplicated version of
 * 			home. It does not handle username postfixes. If that
 * 			duplicated version is null, the tilde expansion will
 * 			not be performed.
 */
void	tilde_exp(t_node *node, t_list *var_list)
{
	char	*tilde_loc;
	char	*temp;
	t_list	*tilde;
	t_wordl	*tmp;

	tmp = node->value.word;
	while (tmp)
	{
		tilde_loc = ft_strchr(tmp->word->value, TILDE);
		if ((tmp->word->flags & W_TILDEEXP) && tilde_loc)
		{
			tilde = lst_get_by_key(var_list, TILDE_VAR);
			if (!tilde || !(tilde->value))
				break ;
			temp = ft_substr(tmp->word->value, 0, \
				(tilde_loc - tmp->word->value));
			temp = ft_strjoin_free(temp, tilde->value);
			temp = ft_strjoin_free(temp, (tilde_loc + 1));
			free(tmp->word->value);
			tmp->word->value = temp;
		}
		tmp = tmp->next;
	}
}
