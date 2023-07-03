/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:52:07 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/03 22:57:30 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_sort(char **env)
{
	int len;
	int i;
	int j;

	i = 0;
	len = ft_strlen_2d((const char **)env);
	len = ft_strlen_2d((const char **)env);
	i = 0;
	while (i < len -1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				ft_swap((void **)&env[i],(void **)&env[j]);
			j++;
		}
		i++;
	}
}

void ft_default(char **env,t_list *var_list)
{
	int i;
	
	i = 0;
	ft_sort(env);
	while (env[i])
	{
		printf("%s %s=\"%s\"\n", DL, *(env + i), lst_get_by_key(var_list, *(env + i))->value);
		i ++;
	}
	free(env);
}

void export(t_list *var_list, t_wordl* args)
{
	char	**env;
	t_wordl *temp;

	temp = args->next;
	env = get_env_key(var_list);
	if (!temp)
		ft_default(env,var_list);
}
