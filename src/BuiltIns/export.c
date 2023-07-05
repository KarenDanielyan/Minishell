/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:52:07 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/05 20:33:42 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lex.h"

void ft_sort(char **env)
{
	int len;
	int i;
	int j;

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

void ft_default(char **env, t_list *var_list)
{
	int		i;
	t_list	*tmp;
	
	i = 0;
	ft_sort(env);
	while (env[i])
	{
		tmp = lst_get_by_key(var_list, *(env + i));
		printf("%s %s", DL, *(env + i));
		if (ft_strchr(tmp->joined, EQUALS))
		{
			printf("=\"");
			if(tmp->value)
				printf("%s", tmp->value);
			printf("\"");
		}
		printf("\n");
		i ++;
	}
}

void export(t_list *var_list, t_wordl* args)
{
	char	**split;
	char	**env;
	t_wordl *temp;

	temp = args->next;
	env = get_env_key(var_list);
	if (!temp)
		ft_default(env, var_list);
	while (temp)
	{
		split = ft_split(temp->word->value, EQUALS);
		if (!is_name(split[0]))
			printf("Minishell: export: `%s': not a valid identifier\n", \
				temp->word->value);
		lst_set_by_word(var_list, temp->word->value);
		free_2d(split);
		temp = temp->next;
	}
	free(env);
}
