/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/11 18:09:52 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

int if_pattern_in_couts(t_wordl *args)
{
	int flag;

	flag = 0;
	while (args)
	{
		if(ft_strchr(args->word->value, '*'))
		{
			flag = 1;
			if ((args->word->flags & W_DQUOTE) || (args->word->flags & W_SQUOTE))
				return(0);
		}
		args = args->next;
	}
	if (!flag)
		return (0);
	return (1);
}

void	glob_exp(t_node *node)
{
	// DIR *dir;
	// char **split;
	char *str;
	t_wordl *args;
	// struct dirent *temp;
	str = "";
	
	args =  node->value.word;
	if (!if_pattern_in_couts(args))
		return ;
	while (args)
	{
		
	}
	
	// str 
	// while ((temp = readdir(dir)) != NULL)
	// 
	// temp = readdir(dir);
	// temp = readdir(dir);
	// temp = readdir(dir);
        // printf("%s\n", temp->d_name);
}
