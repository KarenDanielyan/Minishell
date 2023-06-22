/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:04:29 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/22 17:08:46 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define UNDERSCORE '_'

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