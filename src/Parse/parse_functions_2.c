/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 12:49:57 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 14:38:22 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "parser.h"
#include "minishell.h"
#include <ft_printf.h>

t_node	*parse_command(t_control *ctl, t_token **scanner, int *err)
{
	t_cmdtype	type;
	t_node		*prefix_node;
	t_node		*command_node;

	if (*err)
		return (NULL);
	prefix_node = parse_prefix(ctl, scanner, err);
	if ((*scanner) && (*scanner)->type == SUBSHELL_OPEN)
	{
		type = CompoundCommand;
		command_node = parse_commpound_command(ctl, scanner, err);
	}
	else if (*scanner)
	{
		type = SimpleCommand;
		command_node = parse_simple_command(ctl, scanner, err);
	}
	else
	{
		type = EmptyCommand;
		command_node = NULL;
		if (!prefix_node->value.prefix)
			command_node = parse_error(ctl, scanner, err);
	}
	return (new_command_node(type, prefix_node, command_node));
}

t_node	*parse_commpound_command(t_control *ctl, t_token **scanner, int *err)
{
	t_node	*list_node;
	t_node	*suffix;
	t_node	*ccmd;

	if (*err == 0)
	{
		token_consume(scanner);
		list_node = parse_list(ctl, scanner, err);
		if (!list_node || !(*scanner) || (*scanner)->type != SUBSHELL_CLOSE)
		{
			if (search(ctl, list_node, ErrorNode))
				return (list_node);
			visit(ctl, list_node, drop);
			return (parse_error(ctl, scanner, err));
		}
		list_node->is_last = 0;
		token_consume(scanner);
		suffix = parse_ccmd_suffix(ctl, scanner, err);
		suffix->is_last = 1;
		ccmd = new_ccommand_node(list_node, suffix);
		ccmd->is_last = 1;
		return (ccmd);
	}
	return (NULL);
}

t_node	*parse_simple_command(t_control *ctl, t_token **scanner, int *err)
{
	t_node	*cmd;
	t_node	*suffix;
	t_node	*scmd;

	if (*err == 0)
	{
		if (!(*scanner) || (*scanner)->type != WORD)
			return (parse_error(ctl, scanner, err));
		cmd = parse_word(ctl, scanner, err);
		cmd->is_last = 0;
		suffix = parse_suffix(ctl, scanner, err);
		suffix->is_last = 1;
		scmd = new_scommand_node(cmd, suffix);
		scmd->is_last = 1;
		return (scmd);
	}
	return (NULL);
}
