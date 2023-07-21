/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:47:20 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 18:53:35 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_wordl *args, t_control *ctl)
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
			lst_set(ctl->var_list, ECODE, SUCCESS);
		}
		else
		{
			ft_dprintf(2, ERR_UNSET, temp->word->value);
			lst_set(ctl->var_list, ECODE, FAIL);
		}
		temp = temp->next;
	}
	return (ft_atoi(lst_get_by_key(ctl->var_list, ECODE)->value));
}
