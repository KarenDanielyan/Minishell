/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:44:43 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/21 17:03:51 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include <libft.h>
#include <stdio.h>

static t_flist	*get_builtin(t_control *ctl, t_node *word);

void	execute_scommand(t_control *ctl, t_node *self)
{
	t_flist	*builtin_cmd;

	builtin_cmd = get_builtin(ctl, self->value.s_cmd.word);
	if (builtin_cmd || is_assignment(self->value.s_cmd.word->value.word->word))
		handle_builtin(ctl, self, builtin_cmd);
	else
		handle_command(ctl, self);
}

static t_flist	*get_builtin(t_control *ctl, t_node *word)
{
	char	*name;
	t_flist	*builtins;

	name = word->value.word->word->value;
	builtins = ctl->built_ins;
	while (builtins)
	{
		if (ft_strcmp(builtins->name, name) == 0)
			return (builtins);
		builtins = builtins->next;
	}
	return (builtins);
}
