/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:18:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/02 00:49:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"
# include "lex.h"

typedef struct s_Node			t_Node;
typedef struct s_ListNode		t_ListNode;
typedef struct s_CommandNode	t_CommandNode;
typedef struct s_NodeList		t_PipelineNode;
typedef struct s_sCommandNode	t_sCommandNode;
typedef struct s_cCommandNode	t_cCommandNode;
typedef struct s_NodeList		t_PrefixNode;
typedef struct s_NodeList		t_SuffixNode;
typedef struct s_IORedirectNode	t_IONode;
typedef struct s_wordl			t_WordNode;

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
	t_Node				*node;
	struct s_nodelist	*next;
}	t_NodeList;

typedef struct s_ListNode
{
	t_ListType	type;
	t_Node		*left;
	t_Node		*right;
}	t_ListNode;

typedef struct s_CommandNode
{
	t_CmdType	type;
	t_Node		*prefix;
	t_Node		*command;
}	t_CommandNode;

typedef struct s_sCommandNode
{
	int			flags;
	t_pipe		pipe;
	t_CmdType	type;
	t_Node		*word;
	t_Node		*suffix;
}	t_sCommandNode;

typedef struct s_cCommandNode
{
	t_Node	*list;
	t_Node	*suffix;
}	t_cCommandNode;

typedef struct s_IORedirectNode
{
	t_IOType	type;
	int			fd;
	t_Node	*filename;
}	t_IONode;

typedef union u_NodeValue
{
	t_ListNode		list;
	t_PipelineNode	pipeline;
	t_CommandNode	cmd;
	t_sCommandNode	s_cmd;
	t_cCommandNode	c_cmd;
	t_PrefixNode	prefix;
	t_SuffixNode	suffix;
	t_IONode		redirs;
	t_WordNode		*word;
}	t_NodeValue;

typedef struct s_Node
{
	t_NodeType	node_type;
	t_NodeValue	value;
}	t_Node;

/* Constructors */
t_Node	*new_ListNode(t_ListType type, t_Node *left, t_Node *right);

t_Node	*new_PipelineNode(t_Node *command);

t_Node	*new_CommandNode(t_CmdType type, t_Node *prefix, t_Node *command);

t_Node	*new_SimpleCommandNode(int flags, t_Node *word, t_Node *suffix);

t_Node	*new_CompundCommandNode(t_Node *list, t_Node *suffix);

t_Node	*new_PrefixNode(t_Node *value);

t_Node	*new_SuffixNode(t_Node *value);

t_Node	*newIORedirectNode(t_IOType type, t_Node *filename);

t_Node	*newWordNode(t_wordl *word);

#endif
