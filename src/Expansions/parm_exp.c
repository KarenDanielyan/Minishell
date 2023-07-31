/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parm_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:28:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/31 14:53:32 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expand.h"
#include <libft.h>

static void	escape_quotes(char **param);
static void	apply(t_wordl *head, t_node *self, t_list *var_list);
static void	replace(t_word *word, char **dollar_loc, \
	char *replace_with, int len);
char		*get_param_word(t_list *var_list, char *dollar_loc, int *len);

/**
 * @brief	parm_exp() performs parameter expansion on the word.
 * 			This is not a full version of parameter expansion like bash has,
 * 			it only supports syntax that looks like this: $WORD.
 * 			If you prompt something like this: ${WORD}, it will take
 * 			{WORD} as the word.
*/
void	param_exp(t_node *self, t_list *var_list)
{
	t_wordl	*tmp;
	t_wordl	*next;

	tmp = self->value.word;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->word->flags & W_HASDOLLAR && !(tmp->word->flags & W_SQUOTE))
			apply(tmp, self, var_list);
		tmp = next;
	}
}

static void	apply(t_wordl *head, t_node *self, t_list *var_list)
{
	char	*dollar_loc;
	char	*word;
	int		len;

	len = 0;
	dollar_loc = head->word->value;
	while (1)
	{
		dollar_loc = ft_strchr(dollar_loc, DOLLAR_SIGN);
		if (dollar_loc == NULL)
			break ;
		word = get_param_word(var_list, dollar_loc, &len);
		if (head->word->flags & (W_SQUOTE | W_DQUOTE))
			escape_quotes(&word);
		replace(head->word, &dollar_loc, word, len);
		if (word)
			free(word);
		if (!head->word->value || *(head->word->value) == 0)
		{
			wordl_pop(&(self->value.word), head);
			break ;
		}
	}
}

static void	replace(t_word *word, char **dollar_loc, \
	char *replace_with, int len)
{
	char	*temp;

	if (len == 1)
	{
		(*dollar_loc)++;
		return ;
	}
	temp = ft_substr(word->value, 0, (*dollar_loc - word->value));
	temp = ft_strjoin_free(temp, replace_with);
	temp = ft_strjoin_free(temp, (*dollar_loc + len));
	free(word->value);
	if (temp && *temp == 0)
	{
		free(temp);
		temp = NULL;
	}
	word->value = temp;
	word->flags = word->flags | W_PARMEXP;
	*dollar_loc = word->value;
}

static void	escape_quotes(char **param)
{
	char	*escaped_word;
	char	*i;

	i = *param;
	escaped_word = NULL;
	if (i == NULL)
		return ;
	while (*i)
	{
		if (*i == SQUOTE || *i == DQUOTE)
			ft_strappend(&escaped_word, 1);
		ft_strappend(&escaped_word, *i);
		i++;
	}
	free(*param);
	*param = escaped_word;
}
