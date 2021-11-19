/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:03:08 by dason             #+#    #+#             */
/*   Updated: 2021/11/18 14:46:28 by dason            ###   ########.fr       */
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

char	*remove_char_in_str(char *data, int c)
{
	char	*new_data;
	int		i;
	int		new_data_i;

	new_data = (char *)ft_calloc(ft_strlen(data), sizeof(char));
	if (!new_data)
		exit(1);
	new_data_i = -1;
	i = -1;
	while (data[++i])
	{
		if (data[i] != c)
		{
			new_data[++new_data_i] = data[i];
		}
	}
	printf("origin data: %s\n", data);
	printf("new_data: %s\n", new_data);
	printf("strlen(new_data): %lu\n", ft_strlen(new_data));
	return (new_data);
}

int	check_quote(char *data)
{
	int		i;

	i = -1;
	while (data[++i])
	{
		if (data[i] == '\"')
			return (data[i]);
		if (data[i] == '\'')
			return (data[i]);
	}
	return (0);
}

bool	is_quote(char c)
{
	if (c == '\"')
		return (true);
	if (c == '\'')
		return (true);
	return (false);
}
