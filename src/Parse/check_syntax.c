/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:27:37 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/24 15:47:26 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include <ft_printf.h>

void	check_syntax(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self)
	{
		if (self->type == ErrorNode)
			ft_dprintf(STDERR_FILENO, "%s\n", self->value.error);
		else if (self->type == CmdPrefixNode)
			nodel_check_syntax(self->value.prefix, NULL);
		else if (self->type == CmdSuffixNode)
			nodel_check_syntax(self->value.suffix, NULL);
	}
	else
		return ;
}
