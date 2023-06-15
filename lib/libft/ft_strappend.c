/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:12:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/15 19:19:03 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief		ft_straddpend() append a character `c` to the string str.
 *				If str is NULL, than it will create a new string with the
 * 				character `c` in it.
 * 
 * @param str	String character to be appended to.
 * @param c		Character to be appended.
 * @return int 	Returns 0 on successfull operation, 1 otherwise.
 */
int	ft_strappend(char **str, char c)
{
	const char	s[] = {c, '\0'};
	char		*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, s);
	if (*str == NULL)
	{
		*str = tmp;
		return (1);
	}
	free(*str);
	return (0);
}
