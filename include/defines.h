/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:34:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/02 16:09:24 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stddef.h>

# define HIST_FILE "/.minishell_history"
# define IFS "IFS= \t\n"
# define PS1 "PS1=minishell-0.1& "
# define PS2 "PS2=> "
# define PS4 "PS4=+ "
# define ASSIGN_OP '='

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

typedef enum e_token
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
}	t_token;

/**
 * @brief	Atomic entity of our lexical analysis
 * 
 * @param token_type	What type of word is this? (ex. command io_here, etc.)
 * @param value			The word itself (ex. ">", "<<", "cat")
 */
typedef struct s_word
{
	int		token_type;
	char	*value;
}	t_word;

/**
 * @brief	List of words.
 * 
 */
typedef struct s_wordl
{
	struct s_word	*word;
	struct s_wordl	*next;
}	t_wordl;

#endif