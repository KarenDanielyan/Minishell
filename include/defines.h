/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:34:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/15 14:47:25 by kdaniely         ###   ########.fr       */
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
# define ASSIGN_OP '='
# define OPERATORS "=<>|()&"
# define QUOTES "\'\""

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
	IO_FILE,
	OP_PARAM,
	OP_PIPE,
	AND_IF,
	OR_IF,
	LEFT_PAREN,
	RIGHT_PAREN,
	SQUOTE_OPEN,
	SQUOTE_CLOSE,
	DQUOTE_OPEN,
	DQUOTE_CLOSE,
	WORD
}	t_type;

/**
 * @brief Flags for tokens
 * 
 * @def W_HASDOLLAR		Dollar Sign Present
 * @def W_SQUOTED		Is quoted with a single quote
 * @def W_DQUOTED		Is quoted with a double quote
 * @def W_TILDEEXP		Perform tilde expansion on this assignment word.
 * @def W_NOTILDE		Do not perform tilde expansion.
 * @def W_ASSIGNMENT	This word is a variable assignment.
 * @def W_ASSIGNRHS		Word is rhs of an assignment statement.
 * @def W_ASSIGNLHS		Word is lhs of an assignment statement.
 * @def W_ASSIGNBLTIN	Word is a builtin command that takes assignments.
 * @def W_NOASSNTILDE	Don't do tilde expansion like an assignment statement.
 * @def W_EXPANDRHS		Expanding word in $paramOPword or ${paramOPword}.
 * @def W_ASSIGNARG		Word is assignment argument to command.
 * @def W_HASQUOTEDNULL	Word has a quoted null.
 * @def W_SAWQUOTEDNULL	Word contained a quoted null that was removed.
 * @def W_NOBRACE		Do not perform brace expansion.
 * @def W_COMPLETE		Word is being expansed for completetion.
 * @def W_CHKLOCAL		Check for loacal variables on assignment.
 * @def W_FORCELOCAL	Force assignment to be local variables.
 */
# define W_HASDOLLAR		1
# define W_SQUOTED			2
# define W_DQUOTED			4
# define W_TILDEEXP			8
# define W_NOTILDE			16
# define W_ASSIGNMENT		32
# define W_ASSIGNRHS		64
# define W_ASSIGNLHS		128
# define W_ASSIGNBLTIN		256
# define W_NOASSNTILDE		512
# define W_EXPANDRHS		1024
# define W_ASSIGNARG		2048
# define W_HASQUOTEDNULL	4096
# define W_SAWQUOTEDNULL	8192
# define W_NOBRACE			16384
# define W_COMPLETE			32768
# define W_CHKLOCAL			65536
# define W_FORCELOCAL		131072

/**
 * @brief Possible values for subshell_environment.
 * 
 * @def SUBSHELL_ASYNC	Subshell cause by `command &`
 * @def SUBSHELL_PAREN	Subshell caused by ( ... )
 * @def SUBSHELL_PIPE	Subshell from a pipeline element.
 */
# define SUBSHELL_ASYNC	0x01
# define SUBSHELL_PAREN	0x02
# define SUBSHELL_PIPE	0x10

# define W_SUBSHELL_PAREN	131072 * 2 * SUBSHELL_PAREN
# define W_SUBSHELL_PIPE	131072 * 2 * SUBSHELL_PIPE

#endif