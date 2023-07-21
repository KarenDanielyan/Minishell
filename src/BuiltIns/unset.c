/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:47:20 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 02:14:14 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_wordl *args, t_control *ctl)
{
	t_list	*delete;
	t_wordl	*temp;

	temp = args->next;
	while (temp)
	{
		if (is_name(temp->word->value))
		{
			delete = lst_get_by_key(ctl->var_list, temp->word->value);
			if (delete && delete->type != PRIVATE)
				lst_pop(&ctl->var_list, delete);
		}
		else
		{
			ft_dprintf(2, ERR_UNSET, temp->word->value);
			lst_set(ctl->var_list, SHELL, ECODE, FAIL);
		}
		temp = temp->next;
	}
	lst_set(ctl->var_list, SHELL, ECODE, SUCCESS);
}
