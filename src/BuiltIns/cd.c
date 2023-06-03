/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:29:40 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/03 15:31:42 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *finde(t_list *env, char *key)
{
	t_list *temp;

	temp = env;
	while(temp)
	{
		if (ft_strcmp(key, env->key) == 0)
			return(ft_strdup(env->value));
		temp = temp->next;
	}	
	return (NULL);
}

void change1(t_list *env, char *new)
{
	t_list *temp;
	char	*rem;
	
	temp = env;
	rem = ft_strdup(new);
	while (temp)
	{
		if(ft_strcmp("PWD", temp->key) == 0)
		{
			free(temp->joined);
			free(temp->value);
			temp->value = rem;
			temp->joined = ft_strjoin("PWD=",rem);
			break;
		}
		temp = temp->next;
	}	
}

void change2(t_list *env,char *new)
{
	t_list *temp;

	temp = env;
	while (temp)
	{
		if(ft_strcmp("OLDPWD",temp->key) == 0)
		{
			free(temp->joined);
			free(temp->value);
			temp->value = new;
			temp->joined = (ft_strjoin("OLDPWD=", new));
			break;
		}
		temp = temp->next;
	}
	lst_push_back(&env, lst_new(EXPORT, ft_strjoin("OLDPWD=", new)));//sxala ashxatum
}

void cd(const char *path, t_list *env)
{
	t_list *temp;
	char	*rem_pwd;
	char	*pwd;
	
	temp = env;
	rem_pwd = finde(env, "PWD");
	if (chdir(path) != 0)
		perror("bash: cd: a");
	pwd = getcwd(NULL, 0);
	if(pwd == NULL)
		perror("getcwd() error");
	// change1(env, pwd);
	change2(env, rem_pwd);
	free(pwd);
	free(rem_pwd);
	
	
}

