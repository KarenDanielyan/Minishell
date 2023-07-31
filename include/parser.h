/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:18:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/08/01 02:50:04 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"
# include "lex.h"

/* Constructors */
t_nodel		*nodel_new(t_node *node);

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
t_node		*parse_pipeline_prime(t_control *ctl, t_token **scanner, \
	t_node *expr, int *err);
t_node		*parse_list_prime(t_control *ctl, t_token **scanner, \
	t_node *expr, int *err);
t_node		*parse_commpound_command(t_control *ctl, t_token **scanner, \
	int *err);
t_node		*parse_simple_command(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_ioredirect(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_pipeline(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_command(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_prefix(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_suffix(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_error(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_word(t_control *ctl, t_token **scanner, int *err);
t_node		*parse_list(t_control *ctl, t_token **scanner, int *err);

t_node		*parse_ccmd_suffix(t_control *ctl, t_token **scanner, int *err);

void		token_consume(t_token **scanner);

/* Utils */
t_nodel		*nodel_last(t_nodel *head);
t_nodel		*nodel_prev(t_nodel *head, t_nodel *current);

/* here_doc */
int			parse_heredoc(t_wordl *word, t_control *ctl);
char		*parmexp(char *line, t_control *ctl);

void		set_attr(int mode);

/* Drop Functions */
void		nodel_clear(t_nodel *list, void (*del)(t_node *node));
void		nodel_push(t_nodel **head, t_nodel *to_push);
void		nodel_pop(t_nodel **head, t_nodel *to_pop);
void		drop(t_control *ctl, t_node *self);

/* Syntax Checkers */
void		check_syntax(t_control *ctl, t_node *self);
void		nodel_check_syntax(t_nodel *list, void (*check)(t_node *node));

/* Visit Function for nodelists */
void		nodel_visit(t_control *ctl, t_nodel *list, \
			void (*op)(t_control *ctl, t_node *self));

#endif
