/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:01:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/18 21:26:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

int	is_last(t_node *node)
{
	if (node)
		return (node->is_last);
	else
		return (1);
}

char	*get_node_type(t_nodetype type)
{
	if (type == ListNode)
		return ("\033[34mListNode\033[0m");
	if (type == PipelineNode)
		return ("\033[32mPipelineNode\033[0m");
	if (type == CommandNode)
		return ("\033[34mCommandNode\033[0m");
	if (type == SimpleCommandNode)
		return ("\033[34mSimpleCommandNode\033[0m");
	if (type == CompoundCommandNode)
		return ("\033[34mCompoundCommandNode\033[0m");
	if (type == IORedirectNode)
		return ("\033[32mIORedirectNode\033[0m");
	if (type == CmdPrefixNode)
		return ("\033[32mCmdPrefixNode\033[0m");
	if (type == CmdSuffixNode)
		return ("\033[34mCmdSuffixNode\033[0m");
	if (type == WordNode)
		return ("\033[32mWordNode\033[0m");
	if (type == ErrorNode)
		return ("\033[31mErrorNode\033[0m");
	return (NULL);
}
