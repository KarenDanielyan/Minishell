/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:58:40 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/24 18:33:50 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

static void		set_error_msg(t_nodel **node_list, t_token **scanner);
static t_node	*check_type(t_control *ctl, t_token **scanner, \
	t_IOType *type, int *err);
static t_nodel	*ccmd_suffix_helper(t_control *ctl, \
	t_token **scanner, int *err);

t_node	*parse_ccmd_suffix(t_control *ctl, t_token **scanner, int *err)
{
	t_nodel	*node_list;
	t_node	*node;

	node = NULL;
	if (*err == 0)
	{
		node_list = ccmd_suffix_helper(ctl, scanner, err);
		node = new_suffix_node(node_list);
	}
	return (node);
}

t_node	*parse_ioredirect(t_control *ctl, t_token **scanner, int *err)
{
	t_IOType	type;
	t_node		*node;

	node = NULL;
	if (*err == 0)
	{
		node = check_type(ctl, scanner, &type, err);
		if (node)
			return (node);
		token_consume(scanner);
		if (!(*scanner) || (*scanner)->type != WORD)
			return (parse_error(ctl, scanner, err));
		node = new_io_redirect_node(type, parse_word(ctl, scanner, err));
		if (type == HERE)
		{
			node->value.io.fd = \
				parse_heredoc(node->value.io.filename->value.word, ctl);
			if (node->value.io.fd < 0)
				*err = 1;
		}
	}
	return (node);
}

static t_node	*check_type(t_control *ctl, t_token **scanner, \
	t_IOType *type, int *err)
{
	if ((*scanner)->type == IO_FILE)
	{
		if (*((*scanner)->wordl->word->value) == LESS)
			*type = IN;
		if (*((*scanner)->wordl->word->value) == GREAT)
			*type = OUT;
	}
	else if ((*scanner)->type == IO_APPEND)
		*type = APPEND;
	else if ((*scanner)->type == IO_HERE)
		*type = HERE;
	else
		return (parse_error(ctl, scanner, err));
	return (NULL);
}

t_nodel	*ccmd_suffix_helper(t_control *ctl, t_token **scanner, int *err)
{
	t_nodel	*node_list;

	node_list = NULL;
	if (scanner && *scanner)
	{
		while (*scanner)
		{
			if ((*scanner)->type == IO_FILE || (*scanner)->type == IO_APPEND \
				|| (*scanner)->type == IO_HERE)
				nodel_push(&node_list, \
					nodel_new(parse_ioredirect(ctl, scanner, err)));
			else if ((*scanner)->type == WORD)
			{
				set_error_msg(&node_list, scanner);
				*err = 1;
				break ;
			}
			else
				break ;
		}
		if (node_list)
			nodel_last(node_list)->node->is_last = 1;
	}
	return (node_list);
}

static void	set_error_msg(t_nodel **node_list, t_token **scanner)
{
	t_word	*word;
	char	*error_msg;

	word = wordl_join((*scanner)->wordl);
	error_msg = ft_strjoin(ERROR_MSG, word->value);
	ft_strappend(&error_msg, SQUOTE);
	word_delete(word);
	nodel_push(node_list, nodel_new(new_error_node(error_msg)));
	free(error_msg);
	while (*scanner)
		tok_pop(scanner);
}
