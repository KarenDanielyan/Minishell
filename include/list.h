/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:15:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 16:56:12 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "defines.h"

/* API functions */
int		lst_size(t_list *lst);

t_list	*lst_last(t_list *lst);
t_list	*get_node(t_list *lst, int loc);
t_list	*lst_new(int type, char *key_val);
t_list	*lst_get_by_key(t_list *var_list, char *key);

void	lst_set_by_word(t_list *var_list, t_scope scope, char *assign_word);
void	lst_set(t_list *var_list, t_scope scope, char *key, char *value);
void	lst_clear(t_list **lst, void (*del)(void *));
void	lst_push_front(t_list **lst, t_list *new);
void	lst_push_back(t_list **lst, t_list *new);
void	lst_pop(t_list **lst, t_list *to_pop);

/* Wordlist API */
t_wordl	*wordl_new(t_word *word);
t_wordl	*wordl_dup(t_wordl *head);
t_wordl	*wordl_last(t_wordl *wordl);
t_wordl	*wordl_dup_one(t_wordl *node);
t_wordl	*wordl_find_prev(t_wordl *head, t_wordl *current);
t_wordl	*wordl_sublist(t_wordl *from, t_wordl *to);
t_wordl	*wordl_join_free(t_wordl *sublist);

t_word	*wordl_join(t_wordl *wordl);

void	wordl_clear(t_wordl *wordl);
void	wordl_pop(t_wordl **head, t_wordl *to_pop);
void	wordl_push_back(t_wordl **wordl, t_word *word);
void	wordl_push_front(t_wordl **wordl, t_word *word);

int		wordl_size(t_wordl *head);

char	**wordl_to_array(t_wordl *word);

/* Words */
t_word	*word_new(char *str, int flags);

void	word_delete(t_word *word);

/* flist API */
t_flist	*flist_new(char *name, int (*cmd)(t_wordl *command, t_control *ctl));
t_flist	*flist_last(t_flist *head);

void	flist_push_back(t_flist **head, t_flist *new);
void	flist_clear(t_flist *head);

#endif
