/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:29 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/30 18:29:03 by kdaniely         ###   ########.fr       */
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

	if (ctl->cur_pid != 0)
		ft_dprintf(STDERR_FILENO, "%s\n", EXIT);
	tmp = args->next;
	if (!tmp)
		exit(ft_atoi(lst_get_by_key(ctl->var_list, ECODE)->value));
	jumped = jump_zeros(tmp->word->value);
	rv = check_valid(tmp, jumped);
	free(jumped);
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
	char	*zero_loc;

	i = 0;
	sign = NULL;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			sign = "-";
		i++;
	}
	zero_loc = ft_strchr((num + i), '0');
	if (zero_loc && (zero_loc + 1) && *(zero_loc + 1) == 0)
		return (ft_strdup(num + i));
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
	int64_t		rv;
	char		*s;

	if ((ft_strlen(val) > 19 && *val != '+' && *val != '-') \
		|| ft_strlen(val) > 20)
	{
		ft_dprintf(STDERR_FILENO, EINARG, args->word->value);
		exit(ENUM_ARG);
	}
	rv = ft_atol(args->word->value);
	s = ft_itol(rv);
	if (ft_strcmp(s, val) != 0)
	{
		ft_dprintf(STDERR_FILENO, EINARG, args->word->value);
		exit(ENUM_ARG);
	}
	free(s);
	return (rv);
}
