/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:57:14 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/27 14:53:53 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <readline/readline.h>
#include "minishell.h"

void	true_loop(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$>: ");
		if (ft_strcmp(str, "42") == 0)
			break ;
		printf("User typed: %s\n", str);
		free(str);
	}
}
