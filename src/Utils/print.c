/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:46:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/25 16:07:00 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_print(t_control *ctl, char *key)
{
	t_list	*var;

	var = lst_get_by_key(ctl->var_list, key);
	if (var && var->value)
		ft_dprintf(STDERR_FILENO, "%s", var->value);
}
