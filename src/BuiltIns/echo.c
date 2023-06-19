/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:22:03 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/19 13:53:08 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *flag);

static int	split_siz(char **split);

void	echo(char **split)
{
	int		i;
	int		flag;
	char	*word;

	i = 1;
	word = NULL;
	if (!split[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	flag = check_flag(split[i]);
	if (flag)
		i++;
	while (split[i])
	{
		word = ft_strjoin_free(word, split[i]);
		if (i != split_siz(split) - 1)
			word = ft_strjoin_free(word, " ");
		i++;
	}
	ft_putstr_fd(word, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	free(word);
}

static int	check_flag(char *flag)
{
	size_t	i;

	i = 0;
	if (flag[i] == '-')
		i++;
	while (flag[i] && flag[i] == 'n')
		i++;
	if (i == ft_strlen(flag))
		return (1);
	return (0);
}

static int	split_siz(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
