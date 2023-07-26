/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:40:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/26 00:05:59 by kdaniely         ###   ########.fr       */
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
	char	quote_lvl;
	char	*s;

	quote_lvl = 0;
	while (args)
	{
		s = args->word->value;
		while (*s)
		{
			if (*s == SQUOTE && quote_lvl != DQUOTE)
				quote_lvl ^= SQUOTE;
			if (*s == DQUOTE && quote_lvl != SQUOTE)
				quote_lvl ^= DQUOTE;
			s ++;
		}
		if (quote_lvl != 0)
		{
			ft_dprintf(STDERR_FILENO, "%s%c\'\n", ERROR_QUOTES, quote_lvl);
			return (0);
		}
		args = args->next;
	}
	return (1);
}
