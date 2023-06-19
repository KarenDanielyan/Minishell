/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:29 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/18 21:18:39 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_size(char *num);

void	my_exit(t_list *var_list, char *num)
{
	uint64_t	rv;
	char		*siz;
	char		*s;

	if (!num)
		exit(EXIT_SUCCESS);
	siz = check_size(num);
	if (ft_strlen(siz) > 19)
	{
		dprintf(STDERR_FILENO, "minishell: exit: %s numeric argument required", num);
		exit(1);
	}
	rv = ft_atul(num);
	s = ft_itul(rv);
	if (ft_strcmp(s, (siz)) != 0)
	{
		dprintf(STDERR_FILENO, "minishell: exit: %s numeric argument required", num);
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