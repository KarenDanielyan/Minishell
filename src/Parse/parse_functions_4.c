/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:58:40 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/07 21:24:10 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

static t_node	*check_type(t_token **scanner, t_IOType *type, int *err);

t_node	*parse_ioredirect(t_token **scanner, int *err)
{
	t_IOType	type;
	t_node		*node;

	node = NULL;
	if (*err == 0)
	{
		node = check_type(scanner, &type, err);
		if (node)
			return (node);
		token_consume(scanner);
		if (!(*scanner) || (*scanner)->type != WORD)
			return (parse_error(scanner, err));
		node = new_io_redirect_node(type, parse_word(scanner, err));
	}
	return (node);
}

static t_node	*check_type(t_token **scanner, t_IOType *type, int *err)
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
		return (parse_error(scanner, err));
	return (NULL);
}
