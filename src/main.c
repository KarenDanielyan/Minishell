/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/04 20:05:49 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_shell()
{
	printf(" __       __  __            __            __                  __  __ \n");
	printf("|  \\     /  \\|  \\          |  \\          |  \\                |  \\|  \\ \n");
	printf("| $$\\   /  $$ \\$$ _______   \\$$  _______ | $$____    ______  | $$| $$\n");
	printf("| $$$\\ /  $$$|  \\|       \\ |  \\ /       \\| $$    \\  /      \\ | $$| $$\n");
	printf("| $$$$\\  $$$$| $$| $$$$$$$\\| $$|  $$$$$$$| $$$$$$$\\|  $$$$$$\\| $$| $$\n");
	printf("| $$\\$$ $$ $$| $$| $$  | $$| $$ \\$$    \\ | $$  | $$| $$    $$| $$| $$\n");
	printf("| $$\\$$ $$ $$| $$| $$  | $$| $$ \\$$    \\ | $$  | $$| $$    $$| $$| $$\n");
	printf("| $$ \\$$$| $$| $$| $$  | $$| $$ _\\$$$$$$\\| $$  | $$| $$$$$$$$| $$| $$\n");
	printf("| $$  \\$ | $$| $$| $$  | $$| $$|       $$| $$  | $$ \\$$     \\| $$| $$\n");
	printf(" \\$$      \\$$ \\$$ \\$$   \\$$ \\$$ \\$$$$$$$  \\$$   \\$$  \\$$$$$$$ \\$$ \\$$\n\n");
}

/**
 * @brief	Readline while loop
 */
void	true_loop(t_list *var_l)
{
	int		fd;
	char	*str;
	char	*filename;
	char	**split;

	filename = ft_strjoin(getenv("HOME"), HIST_FILE);
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	free(filename);
	print_shell();
	while (1)
	{
		str = readline("minishell-3.2$ ");
		if (!str)
			break ;
		add_history(str);
		ft_putendl_fd(str, fd);
		split = ft_split(str, ' ');
		if (ft_strcmp(str, "history") == 0)
			history();
		if (ft_strcmp(split[0], "cd") == 0)
			cd(split[1], var_l);
		if (ft_strcmp(str, "pwd") == 0)
			pwd();
		if (ft_strcmp(split[0], "unset") == 0)
		{
			unset_by_key(&var_l, split[1]);
		}
		if (ft_strcmp(str, "env") == 0)
			env(var_l);
		free(split[0]);
		free(split[1]);
		free(split);
		// free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd;
	t_list	*var_l;

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
	var_l = env_init(env);
	true_loop(var_l);
	return (0);
}

