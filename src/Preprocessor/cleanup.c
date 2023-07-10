/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:48:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/10 21:10:53 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include "minishell.h"
#include <libft.h>

static void	cleanup_helper(t_node *self);

/**
 * @brief		Preprocessor module is responsible for moving the multiple
 *	 			fields generated from field splitting and filename expansion,
 *	 			into command arguments node.
 * 				The only node that needs this is the SimpleCommand node,
 * 				as in case of IORedirectNode we should prompt ambiguous
 * 				redirect error, instead moving them into cmd arguments.
 * 
 * @param ctl	The control structure of the program.
 * @param self	The node we want to apply the cleanup function.
 */
void	preprocess(t_control *ctl, t_node *self)
{
	(void)ctl;
	if (self->type == SimpleCommandNode)
		cleanup_helper(self);
	return ;
}

static void	cleanup_helper(t_node *self)
{
	t_node	*word;
	t_node	*suffix;
	t_nodel	*new_head;

	word = self->value.s_cmd.word;
	suffix = self->value.s_cmd.suffix;
	if (wordl_size(word->value.word) != 1)
	{
		new_head = new_node_list(new_word_node(word->value.word->next));
		new_head->node->is_last = 0;
		word->value.word->next = NULL;
		new_head->next = suffix->value.suffix;
		suffix->value.suffix = new_head;
	}
}