/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:56:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/01 02:49:38 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include "parser.h"
#include <libft.h>
#include <stdio.h>

static char	*get_param_word(char *dollar_loc, int *len, t_list *var_list);
static void	replace(char **line, char *dollar_loc, char *word, int len);

void	set_attr(int mode)
{
	static struct termios	ts;

	if (mode == 0)
		tcgetattr(STDIN_FILENO, &ts);
	if (mode == 1)
		tcsetattr(STDIN_FILENO, TCSANOW, &ts);
}

char	*parmexp(char *line, t_control *ctl)
{
	char	*exp_line;
	char	*dollar_loc;
	char	*word;
	int		len;

	exp_line = ft_strtrim(line, "\n");
	while (1)
	{
		dollar_loc = ft_strchr(exp_line, DOLLAR_SIGN);
		if (dollar_loc == NULL)
			break ;
		word = get_param_word(dollar_loc, &len, ctl->var_list);
		replace(&exp_line, dollar_loc, word, len);
		free(word);
		if (!exp_line)
			break ;
	}
	ft_strappend(&exp_line, NEWLINE);
	return (exp_line);
}

static char	*get_param_word(char *dollar_loc, int *len, t_list *var_list)
{
	char	*param;
	char	*word;
	t_list	*param_node;

	*len = 1;
	while (*(dollar_loc + *len) \
		&& (ft_strchr(SYMBS, *(dollar_loc + *len)) == NULL))
		(*len)++;
	param = ft_substr(dollar_loc, 1, (*len - 1));
	param_node = lst_get_by_key(var_list, param);
	if (param_node == NULL)
		word = NULL;
	else
		word = ft_strdup(param_node->value);
	free(param);
	return (word);
}

static void	replace(char **line, char *dollar_loc, char *replace_with, int len)
{
	char	*temp;

	temp = ft_substr(*line, 0, (dollar_loc - *line));
	temp = ft_strjoin_free(temp, replace_with);
	temp = ft_strjoin_free(temp, (dollar_loc + len));
	free(*line);
	if (temp && *temp == 0)
	{
		free(temp);
		temp = NULL;
	}
	*line = temp;
}
