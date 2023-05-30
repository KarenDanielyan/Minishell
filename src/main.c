/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/30 21:40:40 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Readline while loop
 */
void	true_loop(t_list *var_l)
{
	int		fd;
	char	*str;
	char	*filename;

	(void)var_l;
	filename = ft_strjoin(getenv("HOME"), HIST_FILE);
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	free(filename);
	while (1)
	{
		str = readline("minishell-3.2$ ");
		if (!str)
			break ;
		add_history(str);
		ft_putendl_fd(str, fd);
		if (ft_strcmp(str, "history") == 0)
			history();
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd;
	t_list	*var_l;

	if (ac != 2)
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
	var_l = env_init(env);
	true_loop(var_l);
	return (0);
}
