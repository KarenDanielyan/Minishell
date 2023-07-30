/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:50:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/30 16:12:12 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expand.h"
#include <libft.h>

static char	*get_param_name(char *start, int *len);

char	*get_param_word(t_list *var_list, char *dollar_loc, int *len)
{
	char	*param;
	char	*word;
	t_list	*param_node;

	*len = 1;
	param = get_param_name(dollar_loc, len);
	param_node = lst_get_by_key(var_list, param);
	if (param_node == NULL || param_node->type == PRIVATE)
		word = NULL;
	else
		word = ft_strdup(param_node->value);
	free(param);
	return (word);
}

static char	*get_param_name(char *start, int *len)
{
	char	*param;
	char	*tmp;

	param = NULL;
	tmp = NULL;
	if (start)
	{
		while (*(start + *len))
		{
			ft_strappend(&tmp, *(start + *len));
			if (!is_name(tmp))
				break ;
			ft_strappend(&param, *(start + *len));
			(*len)++;
		}
		if (ft_strcmp(tmp, ECODE) == 0)
		{
			param = tmp;
			(*len)++;
		}
		else
			free(tmp);
	}
	return (param);
}
