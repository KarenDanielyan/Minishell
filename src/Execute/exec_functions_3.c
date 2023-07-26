/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:44:43 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/26 14:30:44 by dohanyan         ###   ########.fr       */
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
	t_wordl	*cmd_args;
	t_word	*last_arg;

	cmd_args = NULL;
	last_arg = NULL;
	if (self->value.s_cmd.word)
		cmd_args = self->value.s_cmd.word->value.word;
	if (cmd_args)
		last_arg = wordl_last(cmd_args)->word;
	if (last_arg && last_arg->value)
		lst_set(ctl->var_list, EXPORT, "_", last_arg->value);
	builtin_cmd = get_builtin(ctl, self->value.s_cmd.word);
	if (builtin_cmd || is_assignment(self->value.s_cmd.word->value.word))
		handle_builtin(ctl, self, builtin_cmd);
	else
		handle_command(ctl, self);
}

static t_flist	*get_builtin(t_control *ctl, t_node *word)
{
	char	*name;
	t_flist	*builtins;

	if (!word->value.word)
		return (NULL);
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
