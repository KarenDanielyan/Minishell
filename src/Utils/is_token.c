/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:04:29 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/22 17:31:02 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define UNDERSCORE '_'
#define SQUOTE '\''
#define DQUOTE '\"'

int	is_name(char *str)
{
	if (str && *str)
	{
		if (ft_isalpha(*str) || *str == UNDERSCORE)
		{
			while (*str)
			{
				if (!ft_isalnum(*str) && !ft_isalpha(*str))
					break ;
				str ++;
			}
			if (*str)
				return (0);
			else
				return (1);
		}
		return (0);
	}
	return (0);
}

int	is_quote(char c, int *flags)
{
	int	is_quoted;

	is_quoted = *flags & (W_SQUOTE | W_DQUOTE);
	if (c == SQUOTE && is_quoted == W_SQUOTE)
		return (1);
	if (c == DQUOTE && is_quoted == W_DQUOTE)
		return (1);
	return (0);
}
