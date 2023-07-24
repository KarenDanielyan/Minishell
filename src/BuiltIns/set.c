/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:00:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/24 15:56:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	estat_set(t_control *ctl, int fail);

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
	estat_set(ctl->estat, fail);
	return (fail);
}
