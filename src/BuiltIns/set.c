/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:00:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 17:31:24 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	estat_set(t_control *ctl, int fail);

int	set(t_wordl *args, t_control *ctl)
{
	char	**split;
	char	**env;
	t_wordl	*temp;
	int		fail;

	fail = FALSE;
	temp = args;
	env = get_env_key(ctl->var_list);
	while (temp)
	{
		split = ft_split(temp->word->value, EQUALS);
		if (!is_name(split[0]))
		{
			ft_dprintf(STDERR_FILENO, ERR_EXPORT, temp->word->value);
			fail = TRUE;
		}
		lst_set_by_word(ctl->var_list, LOCAL, temp->word->value);
		free_2d(split);
		temp = temp->next;
	}
	free(env);
	estat_set(ctl, fail);
	return (ft_atoi(lst_get_by_key(ctl->var_list, ECODE)->value));
}

static void	estat_set(t_control *ctl, int fail)
{
	if (fail)
		lst_set(ctl->var_list, SHELL, ECODE, FAIL);
	else
		lst_set(ctl->var_list, SHELL, ECODE, SUCCESS);
}