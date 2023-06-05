/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:47:20 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/05 13:49:27 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_node(t_list *var_l)
{
	free(var_l->joined);
	free(var_l->key);
	free(var_l->value);
	free(var_l);
}

void unset_by_key(t_list **var_l, char *key)
{
	t_list	*tp;
	t_list	*temp;
	t_list	*delete;
	
	tp = NULL;
	temp = NULL;
	delete = lst_get_by_key(*var_l, key);
	if(delete == NULL)
		return ;
	//if in the list is only one node
	if(delete->prev == NULL && delete->next == NULL)
		free_node(delete);
	//if we need to remove the first node
	if(delete->next != NULL && delete->prev == NULL)
	{
		printf("MTELA1\n");
		(*var_l) = (*var_l)->next;
		(*var_l)->prev = NULL;
		delete->next = NULL;
		free_node(delete);
	}

	if(delete->next == NULL && delete->prev)
	{
	// if we need to remove the last node
	printf("MTELA2\n");
		tp = (*var_l);
		tp = lst_last(tp);
		tp = tp->prev;
		tp->next = NULL;
		delete->prev = NULL;
		free_node(delete);
	}
	if(delete->next && delete->prev)
	{
	//if we need to remove middle nodes;
	printf("MTELA3\n");
		tp = delete;
		temp = delete;
		tp = delete->prev;
		temp = delete->next;
		tp->next = temp;
		temp->prev = tp;
		delete->next = NULL;
		delete->prev = NULL;
		free_node(delete);
	}
}