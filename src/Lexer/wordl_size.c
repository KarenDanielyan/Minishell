/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:50:30 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/27 20:50:33 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int wordl_size(t_wordl *wordl)
{
	int i;
	t_wordl *temp;

	i = 0;
	temp = wordl;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}