/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:57:14 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/26 18:01:18 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <readline/readline.h>
#include "minishell.h"

void	true_loop()
{
	char *str;

	while (1)
	{
		str = readline("minishell$>: ");
		if (ft_strcmp(str, "42") == 0)
			break ;
		printf("User typed: %s\n", str);
		free(str);
	}
}