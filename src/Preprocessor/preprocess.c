/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:48:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/20 13:07:09 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include "minishell.h"
#include <libft.h>

static void	move_args(t_node *self);

/**
 * @brief		Preprocessor module is responsible for preparing the parsed
 * 				data for execution. This involves moving the command arguments
 * 				into a command word node.
 * 				This is done for optimization, as it will be easier to create
 * 				an arguments string array from one list, rather that multiple.
 * 				This means that both CmdPrefixNode and CmdSuffixNode will only
 * 				contain IORedirectNodes.
 * 				For making it future-proof, we made it as a seperate module,
 * 				rather that part of word expansions module.
 * 
 * @param ctl	The control structure of the program.
 * @param self	The node we want to apply the preprocessing function.
 */
void	preprocess(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self->type == SimpleCommandNode)
		move_args(self);
	return ;
}

static void	move_args(t_node *self)
{
	t_node	*word;
	t_node	*suffix;
	t_nodel	*i;
	t_nodel	*next;

	word = self->value.s_cmd.word;
	suffix = self->value.s_cmd.suffix;
	i = suffix->value.suffix;
	while (i)
	{
		next = i->next;
		if (i->node->type == WordNode)
		{
			if (word->value.word)
				wordl_last(word->value.word)->next = i->node->value.word;
			else
				word->value.word = i->node->value.word;
			i->node->value.word = NULL;
			nodel_pop(&(suffix->value.suffix), i);
		}
		i = next;
	}
}
