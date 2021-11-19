/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:03:08 by dason             #+#    #+#             */
/*   Updated: 2021/11/19 11:55:15 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	get_num_of_c(char *s, char c)
{
	int	index;
	int	count;

	count = 0;
	index = -1;
	while (s[++index])
	{
		if (s[index] == c)
			count++;
	}
	return (count);
}

int	get_l_type(char *s)
{
	if (*s == '|')
		return (LTYPE_PIPE);
	else if (*s == ';')
		return (LTYPE_SEMI_COLON);
	else if (*s == '<')
		return (LTYPE_REDIRECT);
	else if (*s == '>')
		return (LTYPE_REDIRECT);
	else if (*s == '<' && *(s + 1) == '<')
		return (LTYPE_REDIRECT);
	else if (*s == '>' && *(s + 1) == '>')
		return (LTYPE_REDIRECT);
	else
		return (LTYPE_COMMAND);
}

bool	is_quote(char c)
{
	if (c == '\"')
		return (true);
	if (c == '\'')
		return (true);
	return (false);
}
