/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/28 14:31:43 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief		Readline while loop
 * 
 */
void	true_loop(void)
{
	int		fd;
	char	*str;
	char	*filename;

	filename = ft_strjoin(getenv("HOME"), HIST_FILE);
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	free(filename);
	while (1)
	{
		str = readline("minishell-3.2$ ");
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			ft_putendl_fd(str, fd);
			if (ft_strcmp(str, "history") == 0)
				history();
		}
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	true_loop();
	return (0);
}
