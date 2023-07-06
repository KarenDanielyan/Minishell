/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:25:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 15:58:24 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

void	drop(t_node *node)
{
	if (node)
	{
		if (node->type == WordNode)
			wordl_clear(node->value.word);
		else if (node->type == ErrorNode)
			free(node->value.error);
		free(node);
	}
}
