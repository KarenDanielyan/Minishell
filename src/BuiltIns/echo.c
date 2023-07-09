/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:22:03 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/08 20:28:15 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(t_wordl *temp);

void	echo(t_wordl *wordl)
{
	int		flag;
	char	*word;
	t_wordl	*temp;

	word = NULL;
	temp = NULL;
	if (wordl->next)
		temp = wordl->next;
	if (!temp)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	flag = check_flag(temp);
	if (flag)
		temp = temp->next;
	while (temp)
	{
		word = ft_strjoin_free(word, temp->word->value);
		if (temp->next)
			word = ft_strjoin_free(word, " ");
		temp = temp->next;
	}
	ft_putstr_fd(word, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	free(word);
}

static int	check_flag(t_wordl *temp)
{
	size_t	i;

	i = 0;
	if (!temp)
		return (0);
	if (temp->word->value[i] == '-')
		i++;
	while (temp->word->value[i] && temp->word->value[i] == 'n')
		i++;
	if (i == ft_strlen(temp->word->value))
		return (1);
	return (0);
}
