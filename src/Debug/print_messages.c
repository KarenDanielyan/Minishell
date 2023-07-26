/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:59:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 17:47:40 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_wordl(t_wordl *wordl)
{
	printf("\033[34mValue: ");
	while (wordl)
	{
		printf("\033[32m{%s}\033[0m → ", wordl->word->value);
		wordl = wordl->next;
	}
	printf("NULL\n");
}

void	print_tokens(t_token	*token_list)
{
	while (token_list)
	{
		printf("%p\n", token_list);
		printf("\033[34mToken Type:	\033[32m%s\n\033[0m", \
			get_type(token_list->type));
		print_wordl(token_list->wordl);
		printf("↓\n");
		token_list = token_list->next;
	}
	printf("NULL\n");
}

void	print_env(char **env)
{
	char	**tmp;

	tmp = env;
	while (*tmp)
	{
		printf("%p -> ", *tmp);
		if (*tmp)
			printf("%s", *tmp);
		printf("\n");
		tmp ++;
	}
}
