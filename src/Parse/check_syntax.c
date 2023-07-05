/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:27:37 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 02:53:12 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include <ft_printf.h>

static void	check_syntax_prime2(t_node *self, int *visit);

int	check_syntax(t_node *self)
{
	int	visit;

	visit = 1;
	check_syntax_prime(self, &visit);
	return (visit);
}

void	check_syntax_prime(t_node *self, int *visit)
{
	if (*visit == 0 || self->type == WordNode)
		return ;
	if (self->type == ErrorNode)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", self->value.error);
		*visit = 0;
	}
	if (self->type == ListNode)
	{
		check_syntax_prime(self->value.list.left, visit);
		check_syntax_prime(self->value.list.right, visit);
	}
	else if (self->type == PipelineNode)
	{
		check_syntax_prime(self->value.pipeline.left, visit);
		check_syntax_prime(self->value.pipeline.right, visit);
	}
	else
		check_syntax_prime2(self, visit);
}

static void	check_syntax_prime2(t_node *self, int *visit)
{
	if (self->type == CommandNode)
	{
		check_syntax_prime(self->value.cmd.prefix, visit);
		check_syntax_prime(self->value.cmd.command, visit);
	}
	else if (self->type == CompoundCommandNode)
	{
		check_syntax_prime(self->value.c_cmd.list, visit);
		check_syntax_prime(self->value.c_cmd.suffix, visit);
	}
	else if (self->type == SimpleCommandNode)
	{
		check_syntax_prime(self->value.s_cmd.word, visit);
		check_syntax_prime(self->value.s_cmd.suffix, visit);
	}
	else if (self->type == CmdPrefixNode)
		node_list_check_syntax(self->value.prefix, visit);
	else if (self->type == CmdSuffixNode)
		node_list_check_syntax(self->value.suffix, visit);
	else if (self->type == IORedirectNode)
		check_syntax_prime(self->value.io.filename, visit);
}
