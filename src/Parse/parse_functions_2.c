/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 12:49:57 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 03:05:52 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "parser.h"
#include <ft_printf.h>

t_node	*parse_command(t_token **scanner)
{
	t_cmdtype	type;
	t_node		*prefix_node;
	t_node		*command_node;

	if (!(*scanner))
		return (parse_error(*scanner));
	prefix_node = parse_prefix(scanner);
	if ((*scanner)->type == SUBSHELL_OPEN)
	{
		type = CompoundCommand;
		command_node = parse_commpound_command(scanner);
	}
	else
	{
		type = SimpleCommand;
		command_node = parse_simple_command(scanner);
	}
	return (new_command_node(type, prefix_node, command_node));
}

t_node	*parse_commpound_command(t_token **scanner)
{
	t_node	*list_node;
	t_node	*suffix;
	t_node	*ccmd;

	if ((*scanner)->type != SUBSHELL_OPEN)
		return (parse_error(*scanner));
	token_consume(scanner);
	list_node = parse_list(scanner);
	list_node->is_last = 0;
	if ((*scanner)->type != SUBSHELL_CLOSE)
	{
		drop(list_node);
		return (parse_error(*scanner));
	}
	token_consume(scanner);
	suffix = parse_suffix(scanner);
	suffix->is_last = 1;
	ccmd = new_ccommand_node(list_node, suffix);
	ccmd->is_last = 1;
	return (ccmd);
}

t_node	*parse_simple_command(t_token **scanner)
{
	t_node	*cmd;
	t_node	*suffix;
	t_node	*scmd;

	if ((*scanner)->type != WORD)
		return (parse_error(*scanner));
	cmd = parse_word(scanner);
	cmd->is_last = 0;
	suffix = parse_suffix(scanner);
	suffix->is_last = 1;
	scmd = new_scommand_node(cmd, suffix);
	scmd->is_last = 1;
	return (scmd);
}
