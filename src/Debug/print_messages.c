/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:59:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/19 15:26:09 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_tokens(t_tokl	*token_list)
{
	while (token_list)
	{
		printf("\033[34mToken Type:	\033[32m%s\n\033[0m", get_type(token_list->word->type));
		printf("\033[34mValue:		\033[32m%s\n\033[0m", token_list->word->value);
		printf("↓\n");
		token_list = token_list->next;
	}
}
