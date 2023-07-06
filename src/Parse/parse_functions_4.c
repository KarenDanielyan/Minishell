/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:58:40 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/06 14:33:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

static t_node	*check_type(t_token **scanner, t_IOType *type);

t_node	*parse_ioredirect(t_token **scanner)
{
	t_IOType	type;
	t_wordl		*filename;
	t_node		*node;

	node = NULL;
	if (*scanner)
	{
		node = check_type(scanner, &type);
		if (node)
			return (node);
		token_consume(scanner);
		if ((*scanner)->type != WORD)
			return (parse_error(scanner));
		filename = (*scanner)->wordl;
		(*scanner)->wordl = NULL;
		token_consume(scanner);
		node = new_io_redirect_node(type, new_word_node(filename));
	}
	return (node);
}

static t_node	*check_type(t_token **scanner, t_IOType *type)
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
		return (parse_error(scanner));
	return (NULL);
}
