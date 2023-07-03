/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 12:49:57 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 02:32:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

t_node	*parse_command(t_token **scanner)
{
	t_cmdtype	type;
	t_node		*prefix_node;
	t_node		*command_node;

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

	token_consume(scanner);
	list_node = parse_list(scanner);
	token_consume(scanner);
	suffix = parse_suffix(scanner);
	return (new_ccommand_node(list_node, suffix));
}

t_node	*parse_simple_command(t_token **scanner)
{
	t_node	*cmd;
	t_node	*suffix;

	cmd = parse_word(scanner);
	suffix = parse_suffix(scanner);
	return (new_scommand_node(cmd, suffix));
}
