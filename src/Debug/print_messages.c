/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:59:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/19 15:52:02 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_flags(int flags)
{
	printf("| HASDOLLAR | SQUOTED | DQUOTE | SUBSHELL_PIPE | SUBSHELL_PAREN |\n");
	printf("|      %d    |     %d   |    %d    |      %d       |         %d      |\n",
		flags & W_HASDOLLAR, flags & W_SQUOTE, flags & W_DQUOTE, \
		flags & W_SUBSHELL_PIPE, flags & W_SUBSHELL_PAREN);
}

void	print_tokens(t_tokl	*token_list)
{
	while (token_list)
	{
		print_flags(token_list->word->flags);
		printf("\033[34mToken Type:	\033[32m%s\n\033[0m", get_type(token_list->word->type));
		printf("\033[34mValue:		\033[32m%s\n\033[0m", token_list->word->value);
		printf("↓\n");
		token_list = token_list->next;
		printf("%p\n", token_list);
	}
}
