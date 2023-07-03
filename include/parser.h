/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:18:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/03 16:49:35 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"
# include "lex.h"

typedef struct s_Node			t_node;
typedef struct s_NodeList		t_nodel;
typedef struct s_ListNode		t_lnode;
typedef struct s_CommandNode	t_cnode;
typedef struct s_PipelineNode	t_pipenode;
typedef struct s_sCommandNode	t_scnode;
typedef struct s_cCommandNode	t_ccnode;
typedef struct s_NodeList		t_prefixnode;
typedef struct s_NodeList		t_suffixnode;
typedef struct s_IORedirectNode	t_ionode;
typedef struct s_wordl			t_wordnode;

typedef enum e_NodeType
{
	ListNode,
	PipelineNode,
	CommandNode,
	SimpleCommandNode,
	CompoundCommandNode,
	CmdPrefixNode,
	CmdSuffixNode,
	IORedirectNode,
	WordNode
}	t_NodeType;

typedef enum e_ListType
{
	AND,
	OR
}	t_ListType;

typedef enum e_CmdType
{
	SimpleCommand,
	CompoundCommand
}	t_CmdType;

typedef enum e_IOType
{
	IN,
	OUT,
	HERE,
	APPEND
}	t_IOType;

/**
 * @brief	A list of nodes.
 * 
 * @details	In the background, PipelineNode, PrefixNode, and SuffixNode
 * 			are implemented with this structure.
 */
typedef struct s_NodeList
{
	t_node				*node;
	struct s_NodeList	*next;
}	t_nodel;

typedef struct s_ListNode
{
	t_ListType	type;
	t_node		*left;
	t_node		*right;
}	t_lnode;

typedef struct s_PipelineNode
{
	int	in_fd;
	int	out_fd;
	t_node	*left;
	t_node	*right;
}	t_pipenode;

typedef struct s_CommandNode
{
	t_CmdType	type;
	t_node		*prefix;
	t_node		*command;
}	t_cnode;

typedef struct s_sCommandNode
{
	t_pipe		pipe;
	t_node		*word;
	t_node		*suffix;
}	t_scnode;

typedef struct s_cCommandNode
{
	t_node	*list;
	t_node	*suffix;
}	t_ccnode;

typedef struct s_IORedirectNode
{
	t_IOType	type;
	int			fd;
	t_node		*filename;
}	t_ionode;

typedef union u_NodeValue
{
	t_lnode		list;
	t_pipenode	pipeline;
	t_cnode	cmd;
	t_scnode	s_cmd;
	t_ccnode	c_cmd;
	t_ionode		redirs;
	t_prefixnode	*prefix;
	t_suffixnode	*suffix;
	t_wordnode		*word;
}	t_NodeValue;

typedef struct s_Node
{
	t_NodeType	node_type;
	t_NodeValue	value;
}	t_node;

/* Constructors */
t_node		*new_WordNode(t_wordl *word);

t_node		*new_SuffixNode(t_nodel *value);

t_node		*new_PrefixNode(t_nodel *value);

t_node		*new_PipelineNode(t_node *left, t_node *right);

t_node		*new_IORedirectNode(t_IOType type, t_node *filename);

t_node		*new_SimpleCommandNode(t_node *word, t_node *suffix);

t_node		*new_CompundCommandNode(t_node *list, t_node *suffix);

t_node		*new_ListNode(t_ListType type, t_node *left, t_node *right);

t_node		*new_CommandNode(t_CmdType type, t_node *prefix, t_node *command);

t_nodel		*new_NodeList(t_node *node);

/* Parsing Functions */
t_node		*parse_word(t_token **scanner);

t_node		*parse_list(t_token **scanner);

t_node		*parse_suffix(t_token **scanner);

t_node		*parse_prefix(t_token **scanner);

t_node		*parse_command(t_token **scanner);

t_node		*parse_pipeline(t_token **scanner);

t_node		*parse_ioredirect(t_token **scanner);

t_node		*parse_simple_command(t_token **scanner);

t_node		*parse_commpound_command(t_token **scanner);

t_node		*parse_list_prime(t_token **scanner, t_node *expr);

t_node		*parse_pipeline_prime(t_token **scanner, t_node *expr);

/* TODO: Add peek and consume functions */
t_token		token_peek(t_token *scanner);

void		token_consume(t_token **scanner);

/* Utils */
t_nodel		*list_last(t_nodel *head);

#endif
