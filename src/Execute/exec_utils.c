/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:45:51 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/19 14:51:51 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

char	*get_file_path(char **path, char *file)
{
	char	*file_w_slash;
	char	*join;

	if (access(file, X_OK) == 0)
		return (ft_strdup(file));
	join = NULL;
	if (file && ft_strchr(file, '/') == NULL)
	{
		file_w_slash = ft_strjoin("/", file);
		while (path)
		{
			join = ft_strjoin(*path, file_w_slash);
			if (access(join, X_OK) == 0 || !join)
				break ;
			path ++;
			free(join);
			join = NULL;
		}
		free(file_w_slash);
	}
	return (join);
}

char	**get_path(t_list *var_list)
{
	t_list	*path;
	char	*value;
	char	**split;

	split = NULL;
	path = lst_get_by_key(var_list, PATH);
	if (path)
	{
		value = path->value;
		if (value)
			split = ft_split(value, PATH_DELIM);
	}
	return (split);
}
