/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:04:29 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/15 00:11:57 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name(char *str)
{
	if (str && *str)
	{
		if (*str == DOLLAR_SIGN)
			str ++;
		if (ft_isalpha(*str) || *str == USCORE)
		{
			while (*str)
			{
				if (!ft_isalnum(*str) && !ft_isalpha(*str) && *str != USCORE)
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
	if (is_quoted == 0 && ft_strchr(QUOTES, c))
		return (1);
	if (c == SQUOTE && is_quoted == W_SQUOTE)
		return (1);
	if (c == DQUOTE && is_quoted == W_DQUOTE)
		return (1);
	return (0);
}
