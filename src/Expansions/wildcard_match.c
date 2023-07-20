/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 23:34:02 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/20 23:35:37 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

static void	logic(const char **pattern, const char **string, \
		const char **p, const char **s);

int	wildcard_match(const char *pattern, const char *string)
{
	const char	*p;
	const char	*s;

	p = NULL;
	s = NULL;
	logic(&pattern, &string, &p, &s);
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

static void	logic(const char **pattern, const char **string, \
		const char **p, const char **s)
{
	int	star;

	star = 0;
	while (**string != '\0')
	{
		if (**pattern == **string)
		{
			(*pattern)++;
			(*string)++;
		}
		else if (**pattern == '*')
		{
			star = 1;
			*p = (*pattern)++;
			*s = *string;
		}
		else if (star)
		{
			*pattern = *p + 1;
			*string = ++(*s);
		}
		else
			return ;
	}
}
