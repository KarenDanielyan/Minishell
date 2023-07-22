/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:22:03 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 19:20:14 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(t_wordl *temp);
static char	*create(t_wordl *temp);

int	echo(t_wordl *args, t_control *ctl)
{
	int		flag;
	char	*word;
	t_wordl	*temp;

	(void)ctl;
	word = NULL;
	temp = NULL;
	if (args->next)
		temp = args->next;
	if (!temp)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	flag = check_flag(temp);
	if (flag)
		temp = temp->next;
	word = create(temp);
	ft_putstr_fd(word, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	free(word);
	lst_set(ctl->var_list, ECODE, SUCCESS);
	return (EXIT_SUCCESS);
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

static char	*create(t_wordl *temp)
{
	char	*word;

	word = NULL;
	while (temp)
	{
		word = ft_strjoin_free(word, temp->word->value);
		if (temp->next)
			word = ft_strjoin_free(word, " ");
		temp = temp->next;
	}
	return (word);
}
