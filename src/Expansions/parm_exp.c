/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parm_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:28:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/15 15:35:25 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include <libft.h>

static char	*get_param_word(t_list *var_list, char *dollar_loc, int *len);
static void	replace(t_word *word, char *dollar_loc, \
	char *replace_with, int len);

/**
 * @brief	parm_exp() performs parameter expansion on the word.
 * 			This is not a full version of parameter expansion like bash has,
 * 			it only supports syntax that looks like this: $WORD.
 * 			If you prompt something like this: ${WORD}, it will take
 * 			{WORD} as the word.
*/
void	param_exp(t_node *self, t_list *var_list)
{
	char	*dollar_loc;
	char	*word;
	t_wordl	*tmp;
	int		len;

	tmp = self->value.word;
	len = 0;
	while (tmp)
	{
		if (tmp->word->flags & W_HASDOLLAR && !(tmp->word->flags & W_SQUOTE))
		{
			dollar_loc = ft_strrchr(tmp->word->value, DOLLAR_SIGN);
			word = get_param_word(var_list, dollar_loc, &len);
			replace(tmp->word, dollar_loc, word, len);
			free(word);
		}
		tmp = tmp->next;
	}
}

static char	*get_param_word(t_list *var_list, char *dollar_loc, int *len)
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

static void	replace(t_word *word, char *dollar_loc, char *replace_with, int len)
{
	char	*temp;

	temp = ft_substr(word->value, 0, (dollar_loc - word->value));
	temp = ft_strjoin_free(temp, replace_with);
	temp = ft_strjoin_free(temp, (dollar_loc + len));
	free(word->value);
	word->value = temp;
	word->flags = word->flags | W_PARMEXP;
}
