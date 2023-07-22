/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utilc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:56:25 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/22 15:57:42 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>

char *parmexp(char *line,t_cntrol *tcl)
{
	while (1)
	{
		dollar_loc = ft_strchr(head->word->value, DOLLAR_SIGN);
		if (dollar_loc == NULL)
			break ;
		word = get_param_word(var_list, dollar_loc, &len);
		replace(head->word, dollar_loc, word, len);
		free(word);
		if (!head->word->value || *(head->word->value) == 0)
			wordl_pop(&(self->value.word), head);
	}
}
