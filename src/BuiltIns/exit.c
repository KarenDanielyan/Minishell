/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:29 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/04 20:48:30 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EINARG "minishell: exit: %s numeric argument required"

static char	*check_size(char *num);

void	my_exit(t_list *var_list, t_wordl *wordl)
{
	uint64_t	rv;
	char		*siz;
	char		*s;

	if (!wordl->next)
		exit(EXIT_SUCCESS);
	if (wordl_size(wordl) > 2 && ft_isdigit(wordl->next->word->value[0]))
	{
		ft_dprintf(STDERR_FILENO, "Minishell: exit: too many arguments\n");
		return ;
	}
	siz = check_size(wordl->next->word->value);
	if (ft_strlen(siz) > 19)
	{
		ft_dprintf(STDERR_FILENO, EINARG, num);
		exit(1);
	}
	rv = ft_atul(wordl->next->word->value); 
	s = ft_itul(rv);
	if (ft_strcmp(s, siz) != 0)
	{
		ft_dprintf(STDERR_FILENO, EINARG, num);
		exit(EXIT_FAILURE);
	}
	lst_set(var_list, "?", ft_itoa(rv % 256));
	exit(rv % 256);
}

static char	*check_size(char *num)
{
	int		i;
	char	*sign;

	i = 0;
	sign = NULL;
	if (num[i] == '-' || num[i] == '+')
	{
		sign = "-";
		i++;
	}
	if (num[i] == '0')
	{
		while (num[i] == '0' && num[i])
			i++;
	}
	return (ft_strjoin(sign, (num + i)));
}
