/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:33:26 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/19 01:56:15 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

/* TODO: Add proper function pointers when they are ready */
t_flist	*builtin_init(void)
{
	t_flist	*head;

	flist_push_back(&head, flist_new(CD, NULL));
	flist_push_back(&head, flist_new(ECHO, NULL));
	flist_push_back(&head, flist_new(ENV, NULL));
	flist_push_back(&head, flist_new(EXIT, NULL));
	flist_push_back(&head, flist_new(XPORT, NULL));
	flist_push_back(&head, flist_new(HISTORY, NULL));
	flist_push_back(&head, flist_new(PWD, NULL));
	flist_push_back(&head, flist_new(UNSET, NULL));
	return (head);
}
