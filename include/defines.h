/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:34:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/17 01:45:55 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stddef.h>
# include <stdint.h>

# define EINARG "minishell: exit: %s numeric argument required"
# define ERROR_MSG "minishell: syntax error near unexpected token `"
# define ERROR_EOL "minishell: syntax error: unexpected end of line."
# define ERROR_QUOTES "minishell: unexpected EOL while looking for matching `"
# define ERROR_HIS "numeric argument required"

# define ERR_UNSET "unset: %s: invalid parameter name\n"

# define TILDE_VAR "TILDE"
# define HISTFILE "/.minishell_history"
# define PS1 "PS1=minishell-4.2$ "
# define PS2 "PS2=> "
# define PS4 "PS4=+ "
# define DL "declare -x"
# define NEWLINE '\n'

/* Everything related to field splitting */
# define IFS "IFS"
# define IFS_VAL " \t\n"
# define IFS_INIT "IFS=/"

/* Implemented Operators */
# define OPERATORS "<>|()&"
# define QUOTES "\'\""

/* Terminal Symbols */
# define SYMBS "=<>|()&\'\"$"
# define EQUALS '='
# define PIPE_OP '|'
# define LESS '<'
# define GREAT '>'
# define DLESS "<<"
# define DGREAT ">>"
# define AND_IF "&&"
# define OR_IF "||"
# define LPAREN '('
# define RPAREN ')'
# define DOLLAR_SIGN '$'
# define USCORE '_'
# define SQUOTE '\''
# define SQUOTE_S "\'"
# define DQUOTE '\"'
# define DQUOTE_S "\""
# define ECODE "?"

/* Special Symbols */
# define TILDE '~'
# define CURL_BRACE_L '{'
# define CURL_BRACE_R '}'

/* Platform Specific Defines */
# ifdef __linux__

#  define SYNTAX_ERR "2"

# elif __APPLE__

#  define SYNTAX_ERR "258"

# endif

/**
 * @brief	Variable scope enumeration.
 * 
 * @param LOCAL		Variable declared in a local scope.
 * @param EXPORT	Variable declared with an export keyword.
 * 					Meaning, that variable should be inherited
 * 					by the child processes.
 * @param SHELL		Variables declared by the shell itself.
 * 					Meaning, that this variables are not environmental,
 * 					but should be defined upon invokation of minishell.
 */
typedef enum e_scope
{
	LOCAL,
	EXPORT,
	SHELL,
	PRIVATE
}	t_scope;

/**
 * @brief Variable list structure.
 * 
 * @param type		Determines the scope of the variable.
 * @param joined	string of key-value pair joined with an '='. Ex: 'var=foo'
 * @param key		Variable name.
 * @param value		Value of the varaible.
 * @param prev		Previous variable the variable list.
 * @param next		Next variable in the variable list.
 */
typedef struct s_list
{
	t_scope			type;
	char			*joined;
	char			*key;
	char			*value;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef enum e_type
{
	IO_HERE,
	IO_APPEND,
	IO_FILE,
	OP_PARAM,
	OP_PIPE,
	AND_OP,
	OR_OP,
	VARASSIGN,
	SUBSHELL_OPEN,
	SUBSHELL_CLOSE,
	SQUOTE_OPEN,
	SQUOTE_CLOSE,
	DQUOTE_OPEN,
	DQUOTE_CLOSE,
	WORD,
	UNKNOWN
}	t_type;

/**
 * @brief Flags for tokens
 * 
 * @def W_HASDOLLAR			Dollar Sign Present
 * @def W_SQUOTE			Is quoted with a single quote
 * @def W_DQUOTE			Is quoted with a double quote
 * @def W_TILDEEXP			Perform tilde expansion on this assignment word.
 * @def W_NOTILDE			Do not perform tilde expansion.
 * @def W_SPLIT				Field splitting was performed on the word.
 * @def W_FILEEXP			Filename expansion was performed on the word.
 * @def W_JOIN				This word should be joined with the parts of the
 * 							word that were not field splitted.
 * @def W_ASSIGNMENT		This word is a variable assignment.
 * @def W_ASSIGNRHS			Word is rhs of an assignment statement.
 * 							(NOTE: DEPRICATED)
 * @def W_ASSIGNLHS			Word is lhs of an assignment statement.
 * 							(NOTE: DEPRICATED)
 * @def W_ASSIGNBLTIN		Word is a builtin command that takes assignments.
 * 							(NOTE: DEPRICATED)
 * @def W_NOASSNTILDE		Don't do tilde expansion like an assignment statement.
 * 							(NOTE: DEPRICATED)
 * @def W_PARAMEXP			Expanding word in $param.
 * @def W_ASSIGNARG			Word is assignment argument to command.
 * 							(NOTE: DEPRICATED)
 * @def W_HASQUOTEDNULL		Word has a quoted null.
 * 							(NOTE: DEPRICATED)
 * @def W_SAWQUOTEDNULL		Word contained a quoted null that was removed.
 * 							(NOTE: DEPRICATED)
 * @def W_NOBRACE			Do not perform brace expansion.
 * 							(NOTE: DEPRICATED)
 * @def W_COMPLETE			Word is being expansed for completetion.
 * 							(NOTE: DEPRICATED)
 * @def W_CHKLOCAL			Check for loacal variables on assignment.
 * 							(NOTE: DEPRICATED)
 * @def W_FORCELOCAL		Force assignment to be local variables.
 * 							(NOTE: DEPRICATED)
 * @def W_SUBSHELL_PIPE		Subshell from a pipeline element.
 * @def W_SUBSHELL_PAREN	Subshell caused by ( ... ).
 */
enum e_flags
{
	W_HASDOLLAR			= (1 << 0),
	W_SQUOTE			= (1 << 1),
	W_DQUOTE			= (1 << 2),
	W_TILDEEXP			= (1 << 3),
	W_NOTILDE			= (1 << 4),
	W_SPLIT				= (1 << 5),
	W_FILEEXP			= (1 << 6),
	W_ASSIGNMENT		= (1 << 7),
	W_ASSIGNRHS			= (1 << 8),
	W_ASSIGNLHS			= (1 << 9),
	W_ASSIGNBLTIN		= (1 << 10),
	W_NOASSNTILDE		= (1 << 11),
	W_PARMEXP			= (1 << 12),
	W_ASSIGNARG			= (1 << 13),
	W_HASQUOTEDNULL		= (1 << 14),
	W_SAWQUOTEDNULL		= (1 << 15),
	W_NOBRACE			= (1 << 16),
	W_COMPLETE			= (1 << 17),
	W_CHKLOCAL			= (1 << 18),
	W_FORCELOCAL		= (1 << 19),
	W_SUBSHELL_PAREN	= (1 << 20),
	W_SUBSHELL_PIPE		= (1 << 21),
	W_JOIN				= (1 << 22),
};

typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

/* ****** Defines for lexical analyzer ****** */

/**
 * @brief	Atomic entity of our lexical analysis
 * 
 * @param flags			Flags for the word (refer to defines.h so see possible values).
 * @param value			The word itself (ex. ">", "<<", "cat")
 */
typedef struct s_word
{
	int		flags;
	char	*value;
}	t_word;

/**
 * @brief	Wordlist.
 */
typedef struct s_wordl
{
	struct s_word	*word;
	struct s_wordl	*next;
}	t_wordl;

/**
 * @brief		Generated tokens list. Lexer will return this
 * 				after tokenizing the input.
 * @param type	What type of word is this? (ex. command io_here, etc.)
 */
typedef struct s_token
{
	t_type			type;
	struct s_wordl	*wordl;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/* ****** Defines for syntax analysis and parsing ****** */
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
	WordNode,
	ErrorNode
}	t_nodetype;

typedef enum e_ListType
{
	AND,
	OR
}	t_ListType;

typedef enum e_CmdType
{
	SimpleCommand,
	CompoundCommand,
	EmptyCommand
}	t_cmdtype;

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
	int		in_fd;
	int		out_fd;
	t_node	*left;
	t_node	*right;
}	t_pipenode;

typedef struct s_CommandNode
{
	t_cmdtype	type;
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
	t_lnode			list;
	t_pipenode		pipeline;
	t_cnode			cmd;
	t_scnode		s_cmd;
	t_ccnode		c_cmd;
	t_ionode		io;
	t_prefixnode	*prefix;
	t_suffixnode	*suffix;
	t_wordnode		*word;
	char			*error;
}	t_NodeValue;

typedef struct s_Node
{
	int			is_last;
	t_nodetype	type;
	t_NodeValue	value;
}	t_node;

typedef struct s_control
{
	t_list	*var_list;
	char	*input;
	t_token	*scanner;
	t_node	*tree;
}	t_control;

#endif
