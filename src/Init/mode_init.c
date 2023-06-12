/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:36:56 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/12 13:39:18 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mode_init(int ac, char **av)
{
	int	fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}