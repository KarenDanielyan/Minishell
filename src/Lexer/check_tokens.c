/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:40:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/12 02:51:10 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <libft.h>
#include <ft_printf.h>

static int	check_quotes(t_wordl *args);

int	check_tokens(t_token *scanner)
{
	t_token	*temp;

	temp = scanner;
	while (temp)
	{
		if (temp->type == WORD)
		{
			if (!check_quotes(temp->wordl))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static int	check_quotes(t_wordl *args)
{
	while (args)
	{
		if (ft_strchr(args->word->value, DQUOTE))
		{
			if (ft_strchr(args->word->value, DQUOTE) \
				== ft_strrchr(args->word->value, DQUOTE))
			{
				ft_dprintf(STDERR_FILENO, "%s%c\'\n", ERROR_QUOTES, DQUOTE);
				return (0);
			}
		}
		if (ft_strchr(args->word->value, SQUOTE))
		{
			if (ft_strchr(args->word->value, SQUOTE) \
				== ft_strrchr(args->word->value, SQUOTE))
			{
				ft_dprintf(STDERR_FILENO, "%s%c\'\n", ERROR_QUOTES, SQUOTE);
				return (0);
			}
		}
		args = args->next;
	}
	return (1);
}
