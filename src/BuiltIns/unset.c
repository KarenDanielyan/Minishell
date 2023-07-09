/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:47:20 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/09 18:51:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_list **var_list, t_wordl *wordl)
{
	t_list	*delete;
	t_wordl	*temp;

	temp = wordl->next;
	if (!temp)
	{
		ft_dprintf(STDERR_FILENO, "unset: not enough arguments\n");
		return ;
	}
	while (temp)
	{
		if (is_name(temp->word->value))
		{
			delete = lst_get_by_key(*var_list, temp->word->value);
			if (delete->type != PRIVATE)
				lst_pop(var_list, delete);
		}
		else
			ft_dprintf(2, ERR_UNSET, temp->word->value);
		temp = temp->next;
	}
}
