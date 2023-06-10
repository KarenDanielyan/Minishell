/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/10 16:02:55 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shell(void)
{
	// printf(" __       __  __            __            __                  __  __ \n");
	// printf("|  \\     /  \\|  \\          |  \\          |  \\                |  \\|  \\ \n");
	// printf("| $$\\   /  $$ \\$$ _______   \\$$  _______ | $$____    ______  | $$| $$\n");
	// printf("| $$$\\ /  $$$|  \\|       \\ |  \\ /       \\| $$    \\  /      \\ | $$| $$\n");
	// printf("| $$$$\\  $$$$| $$| $$$$$$$\\| $$|  $$$$$$$| $$$$$$$\\|  $$$$$$\\| $$| $$\n");
	// printf("| $$\\$$ $$ $$| $$| $$  | $$| $$ \\$$    \\ | $$  | $$| $$    $$| $$| $$\n");
	// printf("| $$\\$$ $$ $$| $$| $$  | $$| $$ \\$$    \\ | $$  | $$| $$    $$| $$| $$\n");
	// printf("| $$ \\$$$| $$| $$| $$  | $$| $$ _\\$$$$$$\\| $$  | $$| $$$$$$$$| $$| $$\n");
	// printf("| $$  \\$ | $$| $$| $$  | $$| $$|       $$| $$  | $$ \\$$     \\| $$| $$\n");
	// printf(" \\$$      \\$$ \\$$ \\$$   \\$$ \\$$ \\$$$$$$$  \\$$   \\$$  \\$$$$$$$ \\$$ \\$$\n\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗%s", \
	"███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║%s", \
	"██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║%s", \
	"███████╗███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║%s", \
	"╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║%s", \
	"███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝%s", \
	"╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}

void	ft_irc(int signum)
{
	if(signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = -475836;
	}
}

/**
 * @brief	Readline while loop
 */
void	true_loop(t_list *var_l)
{
	char	*str;
	int		fd;
	char	**split;
	char	*filename;
	struct sigaction sa;
	
	sa.sa_handler = &ft_irc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	
	filename = ft_strjoin(getenv("HOME"), HIST_FILE);
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	free(filename);
	print_shell();
	while (1)
	{
		str = readline(lst_get_by_key(var_l, "PS1")->value);
		if (!str)
			break ;
		if (!(*str))
		{
			free(str);
			continue ;
		}
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
			unset(&var_l, split[1]);
		if (ft_strcmp(str, "env") == 0)
			env(var_l);
		free_2d(split);
	}
}

int	main(int ac, char **av, char **env)
{
	t_list	*var_l;
	int fd;
	// char	*filename;

	// filename = ft_strjoin(getenv("HOME"), HIST_FILE);
	// h_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	// free(filename);
	// print_shell();

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
