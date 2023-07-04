/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:01:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 18:13:40 by kdaniely         ###   ########.fr       */
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
	return (NULL);
}

void	print_value(t_node *node)
{
	t_wordl	*tmp;

	if (node)
	{
		printf(": ");
		if (node->type == ListNode)
		{
			if(node->value.list.type == AND)
				printf("{%s}", AND_IF);
			else
				printf("{%s}", OR_IF);
		}
		else if (node->type == WordNode)
		{
			tmp = node->value.word;
			while(tmp)
			{
				printf("\033[32m{%s}\033[0m → ", tmp->word->value);
				tmp = tmp->next;
			}
			printf("NULL");
		}
	}
	printf("\n");
}
