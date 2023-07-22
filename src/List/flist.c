/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:37:31 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 16:55:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

t_flist	*flist_new(char *name, int (*cmd)(t_wordl *command, t_control *ctl))
{
	t_flist	*new;

	new = (t_flist *)malloc(sizeof(t_flist));
	if (!new)
	{
		perror(EPERROR);
		exit(EXIT_FAILURE);
	}
	new->cmd = cmd;
	new->name = name;
	new->next = NULL;
	return (new);
}

void	flist_push_back(t_flist **head, t_flist *new)
{
	if (head)
	{
		if (*head)
			flist_last(*head)->next = new;
		else
			*head = new;
	}
}

t_flist	*flist_last(t_flist *head)
{
	if (head)
	{
		while (head->next)
			head = head->next;
	}
	return (head);
}

void	flist_clear(t_flist *head)
{
	t_flist	*next;

	if (head)
	{
		while (head)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}
}
