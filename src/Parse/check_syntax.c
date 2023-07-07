/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:27:37 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/07 16:28:29 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include <ft_printf.h>

void	check_syntax(t_node *self)
{
	if (self)
	{
		if (self->type == ErrorNode)
			ft_dprintf(2, "%s\n", self->value.error);
		else if (self->type == CmdPrefixNode)
			node_list_check_syntax(self->value.prefix);
		else if (self->type == CmdSuffixNode)
			node_list_check_syntax(self->value.suffix);
	}
	else
		return ;
}
