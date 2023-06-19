/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:14:07 by kdaniely          #+#    #+#             */
/*   Updated: 2023/06/19 15:22:10 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

char	*get_type(int type)
{
	if (type == 0)
		return ("IO_HERE");
	if (type == 1)
		return ("IO_APPEND");
	if (type == 2)
		return ("IO_FILE");
	if (type == 3)
		return ("OP_PARAM");
	if (type == 4)
		return ("OP_PIPE");
	if (type == 5)
		return ("AND_IF");
	if (type == 6)
		return ("OR_IF");
	if (type == 7)
		return ("VARASSIGN");
	if (type == 8)
		return ("LEFT_PAREN");
	if (type == 9)
		return ("RIGHT_PAREN");
	if (type == 10)
		return ("SQUOTE_OPEN");
	if (type == 11)
		return ("SQUOTE_CLOSE");
	if (type == 12)
		return ("DQUOTE_OPEN");
	if (type == 13)
		return ("DQUOTE_CLOSE");
	if (type == 14)
		return ("WORD");
	return ("NOTOP");
}