/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordl_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:02:25 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 21:12:15 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <libft.h>

int	wordl_size(t_wordl *head)
{
	int	i;

	i = 0;
	if (head)
	{
		while (head->next)
		{
			head = head->next;
			i ++;
		}
	}
	return (i);
}