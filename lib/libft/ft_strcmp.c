/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:43:31 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/31 18:40:40 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	char	*c1;
	char	*c2;

	c1 = (char *)s1;
	c2 = (char *)s2;
	if (!s1 || !s2)
		return (-1);
	while (*c1 || *c2)
	{
		if (*c1 != *c2)
			return ((unsigned char)(*c1 - *c2));
		c1 ++;
		c2 ++;
	}
	return (0);
}
