/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:34:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/30 19:08:46by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stddef.h>

# define HISTFILE "/.minishell_history"
# define IFS "IFS= \t\n"
# define PS1 "PS1=minishell-4.2$ "
# define PS2 "PS2=> "
# define PS4 "PS4=+ "

# define NEWLINE '\n'

# define OPERATORS "<>|()&"
# define QUOTES "\'\""

/* Terminal Symbols */
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
# define DQUOTE '\"'

/* Special Symbols */
# define TILDE '~'

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
	SHELL
}	t_scope;

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
	W_ASSIGNMENT		= (1 << 5),
	W_ASSIGNRHS			= (1 << 6),
	W_ASSIGNLHS			= (1 << 7),
	W_ASSIGNBLTIN		= (1 << 8),
	W_NOASSNTILDE		= (1 << 9),
	W_PARMEXP			= (1 << 10),
	W_ASSIGNARG			= (1 << 11),
	W_HASQUOTEDNULL		= (1 << 12),
	W_SAWQUOTEDNULL		= (1 << 13),
	W_NOBRACE			= (1 << 14),
	W_COMPLETE			= (1 << 15),
	W_CHKLOCAL			= (1 << 16),
	W_FORCELOCAL		= (1 << 17),
	W_SUBSHELL_PAREN	= (1 << 18),
	W_SUBSHELL_PIPE		= (1 << 19)
};

typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

#endif
