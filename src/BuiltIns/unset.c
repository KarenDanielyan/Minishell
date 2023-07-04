/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:47:20 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/28 20:22:35 by dohanyan         ###   ########.fr       */
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
		delete = lst_get_by_key(*var_list, temp->word->value);
		lst_pop(var_list, delete);
		temp = temp->next;
	}
}
