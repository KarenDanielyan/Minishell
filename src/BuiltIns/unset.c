/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:47:20 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/09 22:42:51 by dohanyan         ###   ########.fr       */
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
			if (delete && delete->type != PRIVATE)
				lst_pop(var_list, delete);
		}
		else
		{
			ft_dprintf(2, ERR_UNSET, temp->word->value);
			lst_set(*var_list, ECODE, "1");
		}
		temp = temp->next;
	}
}
