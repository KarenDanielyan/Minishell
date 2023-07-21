/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:29 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/21 02:17:53 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lex.h"

static char	*check_size(char *num);
static void	check_valid(t_wordl *wordl, t_list *var_list);

void	my_exit(t_wordl *args, t_control *ctl)
{
	uint64_t	rv;
	char		*siz;
	char		*s;

	check_valid(args, ctl->var_list);
	siz = check_size(args->next->word->value);
	if (ft_strlen(siz) > 19)
	{
		ft_dprintf(STDERR_FILENO, EINARG, args->next->word->value);
		exit(1);
	}
	rv = ft_atul(args->next->word->value);
	s = ft_itul(rv);
	if (ft_strcmp(s, siz) != 0)
	{
		ft_dprintf(STDERR_FILENO, EINARG, args->next->word->value);
		exit(EXIT_FAILURE);
	}
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

static void	check_valid(t_wordl *wordl, t_list *var_list)
{
	if (!wordl->next)
		exit(EXIT_SUCCESS);
	if (wordl_size(wordl) > 2 && ft_isdigit(wordl->next->word->value[0]))
	{
		ft_dprintf(STDERR_FILENO, "Minishell: exit: too many arguments\n");
		lst_set(var_list, SHELL, ECODE, FAIL);
		return ;
	}
}
