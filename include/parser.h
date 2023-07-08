/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:18:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/07 22:39:20 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"
# include "lex.h"

/* Constructors */
t_nodel		*new_node_list(t_node *node);

t_node		*new_error_node(char *msg);
t_node		*new_word_node(t_wordl *word);
t_node		*new_suffix_node(t_nodel *value);
t_node		*new_prefix_node(t_nodel *value);
t_node		*new_pipeline_node(t_node *left, t_node *right);
t_node		*new_scommand_node(t_node *word, t_node *suffix);
t_node		*new_ccommand_node(t_node *list, t_node *suffix);
t_node		*new_io_redirect_node(t_IOType type, t_node *filename);
t_node		*new_list_node(t_ListType type, t_node *left, t_node *right);
t_node		*new_command_node(t_cmdtype type, t_node *prefix, t_node *command);

/* Parsing Functions */
t_node		*parse_pipeline_prime(t_token **scanner, t_node *expr, int *err);
t_node		*parse_list_prime(t_token **scanner, t_node *expr, int *err);
t_node		*parse_commpound_command(t_token **scanner, int *err);
t_node		*parse_simple_command(t_token **scanner, int *err);
t_node		*parse_ioredirect(t_token **scanner, int *err);
t_node		*parse_pipeline(t_token **scanner, int *err);
t_node		*parse_command(t_token **scanner, int *err);
t_node		*parse_prefix(t_token **scanner, int *err);
t_node		*parse_suffix(t_token **scanner, int *err);
t_node		*parse_error(t_token **scanner, int *err);
t_node		*parse_word(t_token **scanner, int *err);
t_node		*parse_list(t_token **scanner, int *err);

void		token_consume(t_token **scanner);

/* Utils */
t_nodel		*list_last(t_nodel *head);

/* Drop Functions */
void	drop(t_node *tree);
void	node_list_clear(t_nodel *list, void (*del)(t_node *node));

/* Syntax Checkers */
void	node_list_check_syntax(t_nodel *list);
void	node_list_visit(t_nodel *list, void (*op)(t_node *self));

#endif
