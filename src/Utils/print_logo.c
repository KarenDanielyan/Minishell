/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:09:46 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/22 19:53:53 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_logo(void)
{
	printf("\033[38;2;15;60;76m███╗   ███╗██╗███╗   ██╗██╗%s", \
	"███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("\033[38;2;15;60;76m████╗ ████║██║████╗  ██║██║%s\033[0m", \
	"██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("\033[38;2;15;60;76m██╔████╔██║██║██╔██╗ ██║██║%s\033[0m", \
	"███████╗███████║█████╗  ██║     ██║     \n");
	printf("\033[38;2;15;60;76m██║╚██╔╝██║██║██║╚██╗██║██║%s\033[0m", \
	"╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("\033[38;2;15;60;76m██║ ╚═╝ ██║██║██║ ╚████║██║%s\033[0m", \
	"███████║██║  ██║███████╗███████╗███████╗\n");
	printf("\033[38;2;15;60;76m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝%s\033[0m", \
	"╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}
