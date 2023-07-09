/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parm_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:28:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/09 17:35:56 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

/**
 * @brief	parm_exp() performs parameter expansion on the word.
 * 			This is not a full version of parameter expansion like bash has,
 * 			it only supports syntax that looks like this: $WORD and ${WORD}.
*/
void	parm_exp(t_list *var_list, t_node *self)
{
	char	*dollar_loc;
	char	*temp;
	t_list	*tilde;
	t_wordl	*tmp;

	tmp = node->value.word;
	while (tmp)
	{
		if (tmp->word->flags & W_HASDOLLAR)
		{
			dollar_loc = ft_strrchr(tmp->word->value, DOLLAR_SIGN);
			temp = 
		}
		tmp = tmp->next;
	}
}

static void	get_word