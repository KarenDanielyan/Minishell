/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:33:30 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/10 00:09:47 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

void	quote_removal(t_node *self)
{
	t_wordl	*temp;
	char	*tmp;

	tmp = NULL;
	temp = self->value.word;
	while (temp)
	{
		if (temp->word->flags & W_DQUOTE)
			tmp = ft_strtrim(temp->word->value, DQUOTE_S);
		if (temp->word->flags & W_SQUOTE)
			tmp = ft_strtrim(temp->word->value, SQUOTE_S);
		if (tmp != NULL)
		{
			free(temp->word->value);
			temp->word->value = tmp;
		}
		tmp = NULL;
		temp = temp->next;
	}
}
