/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:24:49 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/28 23:19:01 by kdaniely         ###   ########.fr       */
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
 * 			not be performed. The only possible way to use tilde
 * 			is this:
 * 			~
 * 			If word contains any other character except tilde,
 * 			tilde expansion will not be performed.
 */
void	tilde_exp(t_node *node, t_list *var_list)
{
	t_list	*tilde;
	t_wordl	*tmp;

	tmp = node->value.word;
	if (wordl_size(tmp) == 1)
	{
		if (ft_strlen(tmp->word->value) == 1 && *(tmp->word->value) == TILDE)
		{
			tilde = lst_get_by_key(var_list, TILDE_VAR);
			if (!tilde || !(tilde->value))
				return ;
			free(tmp->word->value);
			tmp->word->value = ft_strdup(tilde->value);
		}
	}
}
