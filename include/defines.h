/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:34:35 by kdaniely          #+#    #+#             */
/*   Updated: 2023/05/26 19:08:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

typedef enum e_token
{
	io_here,
	io_file_in,
	io_file_out,
	op_pipe,
	and_if,
	or_if,
	left_paren,
	right_paren,
	op_pipe,
	op_squote_open,
	op_squote_close,
	op_dquote_open,
	op_dquote_close,
	op_param,
	word
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
 * @brief	List of word.
 * 
 */
typedef struct s_wordl
{
	struct s_word	*word;
	struct s_wordl	*next;
}

#endif