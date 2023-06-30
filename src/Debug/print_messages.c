/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:59:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/30 17:28:28 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_flags(int flags)
{
	printf("| HASDOLLAR | SQUOTED | DQUOTE | SUBSHELL_PIPE | SUBSHELL_PAREN |\n");
	printf("|      %d    |    %d    |    %d   |       %d       |         %d      |\n",
		((flags & W_HASDOLLAR) != 0), ((flags & W_SQUOTE) != 0), ((flags & W_DQUOTE) != 0), \
		((flags & W_SUBSHELL_PIPE) != 0), ((flags & W_SUBSHELL_PAREN) != 0));
}

void	print_wordl(t_wordl *wordl)
{
	printf("\033[34mValue: ");
	while (wordl)
	{
		printf("\033[32m{%s}\033[0m → ", wordl->word->value);
		wordl = wordl->next;
	}
	printf("\n");
}

void	print_tokens(t_token	*token_list)
{
	while (token_list)
	{
		printf("%p\n", token_list);
		print_flags(token_list->wordl->word->flags);
		printf("\033[34mToken Type:	\033[32m%s\n\033[0m", get_type(token_list->type));
		print_wordl(token_list->wordl);
		printf("↓\n");
		token_list = token_list->next;
	}
}
