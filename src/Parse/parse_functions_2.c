/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 12:49:57 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/02 15:24:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

t_node	*parse_command(t_token **scanner)
{
	t_CmdType	type;
	t_node		*prefix_node;
	t_node		*command_node;

	prefix_node = parse_prefix(scanner);
	if ((*scanner)->type == SUBSHELL_OPEN)
	{
		command_node = parse_commpound_command(scanner);
		type = CompoundCommand;
	}
	else
	{
		command_node = parse_simple_command(scanner);
		type = SimpleCommand;
	}
	return (new_CommandNode(type, prefix_node, command_node));
}

t_node	*parse_commpound_command(t_token **scanner)
{
	t_node	*list_node;
	t_node	*suffix;

	token_consume(scanner);
	list_node = parse_list(scanner);
	token_consume(scanner);
	suffix = parse_suffix(scanner);
	return (new_CompundCommandNode(list_node, suffix));
}

t_node	*parse_simple_command(t_token **scanner)
{
	t_node	*cmd;
	t_node	*suffix;

	cmd = parseWord(scanner);
	suffix = parse_suffix(scanner);
	return (new_SimpleCommandNode(cmd, suffix));
}
