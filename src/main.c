/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/24 22:44:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main()
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
	return (0);
}
