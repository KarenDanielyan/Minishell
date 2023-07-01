/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:18:20 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/01 20:28:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"
# include "lex.h"

/**
 * @brief Contex-Free Grammar
 * 
 * Terminal Symbols are defined at "defines.h"
 * 
 * Non-Terminal Symbols:
 * 
 * program			:= list
 * 					;
 * list				:= pipeline list'
 * 					;
 * list'			:= (AND_IF | OR_IF) pipeline list' | NULL
 * 					;
 * pipeline			:= command (PIPE_OP command)
 * 					;
 * command			:= cmd_prefix? (compound_command | simple_command)
 * 					;
 * compound_command	:= subshell cmd_suffix?
 * 					;
 * subshell			:= LPAREN list RPAREN
 * 					;
 * simple_command	:= cmd_word cmd_suffix?
 * 					;
 * cmd_word			:= WORD
 * 					;
 * cmd_prefix		:= io_redirect*
 * 					;
 * cmd_suffix		:= (WORD | io_redirect)*
 * 					;
 * io_redirect		:= io_file | io_here
 * 					;
 * io_file			:= LESS filename
 * 					| GREAT filename
 * 					| DGREAT filename
 * 					;
 * filename			:= WORD
 * 					;
 * io_here			:= DLESS here_end
 * 					;
 * here_end			:= WORD
 * 					;
 */

typedef struct s_ListNode		t_ListNode;
typedef struct s_PipelineNode	t_PipelineNode;
typedef struct s_CommandNode	t_CommandNode;
typedef struct s_sCommandNode	t_sCommandNode;
typedef struct s_cCommandNode	t_cCommandNode;
typedef struct s_PrefixNode		t_PrefixNode;
typedef struct s_SuffixNode		t_SuffixNode;
typedef struct s_IORedirNode	t_IONode;
typedef struct s_wordl			t_WordNode;

typedef enum e_type
{
	ListNode,
	PipelineNode,
	CommandNode,
	SimpleCommandNode,
	CompoundCommandNode,
	CmdPrefixNode,
	CmdSuffixNode
	IORedirectNode
}	t_NodeType;

typedef enum e_ListType
{
	AND,
	OR
}	t_ListType;

typedef union u_NodeValue
{
	t_ListNode		list;
	t_PipelineNode	pipel;
	t_CommandNode	cmd;
	t_sCommandNode	s_cmd;
	t_cCommandNode	c_cmd;
	t_PrefixNode	prefix;
	t_SuffixNode	suffix;
	t_IONode		redirs;
	t_WordNode		word;
}	t_NodeValue;

typedef struct s_Node
{
	t_type		node_type;
	t_NodeValue	value;
}	t_Node;

/**
 * @brief A list of nodes
 * 
 * 
 * May be needed for cmd_prefix and cmd_suffix
 */
typedef struct s_NodeList
{
	t_Node				*node;
	struct s_nodelist	*next;
}	t_NodeList;

typedef struct s_listNode
{
	t_ListType	type;
	t_Node		*left;
	t_Node		*right;
}	t_Node;

#endif
