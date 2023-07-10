/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:37:10 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/10 14:36:38 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>
#include <dirent.h>
#include <stdio.h>

void	glob_exp(t_node *node)
{
	(void)node;
	// char **split;
	// t_wordl *args;
	// struct dirent *temp;
	
	// dir = opendir(".");
	// split = ft_split(node->value.word->word->value);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%s\n",node->value.word->word->value);
	// while ((temp = readdir(dir)) != NULL) 
    //     printf("%s\n", temp->d_name);
}
