/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:29 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/24 15:47:40 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lex.h"

static char		*jump_zeros(char *num);
static int		check_valid(t_wordl *args, char *val);
static uint64_t	check_numeric_arg(t_wordl *args, char *val);

int	my_exit(t_wordl *args, t_control *ctl)
{
	t_wordl		*tmp;
	int			rv;
	char		*jumped;

	ft_dprintf(STDERR_FILENO, "%s\n", EXIT);
	tmp = args->next;
	if (!tmp)
		exit(EXIT_SUCCESS);
	jumped = jump_zeros(tmp->word->value);
	rv = check_valid(tmp, jumped);
	if (rv < 0)
	{
		estat_set(ctl->estat, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	exit(rv);
	return (EXIT_SUCCESS);
}

static char	*jump_zeros(char *num)
{
	int		i;
	char	*sign;

	i = 0;
	sign = NULL;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
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

static int	check_valid(t_wordl *args, char *val)
{
	uint64_t	rv;

	rv = check_numeric_arg(args, val);
	if (wordl_size(args) > 1)
	{
		ft_dprintf(STDERR_FILENO, E2MUCH);
		return (-1);
	}
	return ((int)(rv % 256));
}

static uint64_t	check_numeric_arg(t_wordl *args, char *val)
{
	uint64_t	rv;
	char		*s;

	if (ft_strlen(val) > 19)
	{
		ft_dprintf(STDERR_FILENO, EINARG, args->word->value);
		exit(EXIT_FAILURE);
	}
	rv = ft_atul(args->word->value);
	s = ft_itul(rv);
	if (ft_strcmp(s, val) != 0)
	{
		ft_dprintf(STDERR_FILENO, EINARG, args->word->value);
		exit(EXIT_FAILURE);
	}
	free(s);
	return (rv);
}
