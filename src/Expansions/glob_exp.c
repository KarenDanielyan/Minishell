/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/10 21:19:03 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

void	glob_exp(t_node *node)
{	DIR *dir;
	char **split;
	char *str;
	t_wordl *args;
	struct dirent *temp;
	str = "";
	
	args =  node->value.word;
	while ()
	{
		
	}
	
	// str 
	// while ((temp = readdir(dir)) != NULL)
	// 
	// temp = readdir(dir);
	// temp = readdir(dir);
	// temp = readdir(dir);
        printf("%s\n", temp->d_name);
}
