/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_organize_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:41:36 by dason             #+#    #+#             */
/*   Updated: 2021/11/24 11:49:52 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	str_addback_quote(char **new_str, char *str, int *i, int *new_i)
{
	int		quote;

	quote = str[*i];
	while (str[*i])
	{
		(*new_str)[(*new_i)++] = str[(*i)++];
		if (str[*i] == quote)
		{
			(*new_str)[(*new_i)++] = str[(*i)++];
			break ;
		}
	}
}

static void	str_addback_ltype(char **new_str, char *str, int *i, int *new_i)
{
	if (get_l_type(&str[*i]) == LTYPE_REDIRECT2_L || \
		get_l_type(&str[*i]) == LTYPE_REDIRECT2_R)
	{
		if (*new_i != 0 && (*new_str)[*new_i - 1] != ' ')
			(*new_str)[(*new_i)++] = ' ';
		(*new_str)[(*new_i)++] = str[(*i)++];
		(*new_str)[(*new_i)++] = str[(*i)++];
		(*new_str)[(*new_i)++] = ' ';
	}
	else if (get_l_type(&str[*i]) != LTYPE_COMMAND)
	{
		if (*new_i != 0 && (*new_str)[*new_i - 1] != ' ')
			(*new_str)[(*new_i)++] = ' ';
		(*new_str)[(*new_i)++] = str[(*i)++];
		(*new_str)[(*new_i)++] = ' ';
	}
	else if (is_quote(str[*i]))
		str_addback_quote(new_str, str, i, new_i);
	else
		(*new_str)[(*new_i)++] = str[*i];
}

char	*organize_input_str(char *str)
{
	char	*new_str;
	int		count_ltype;
	int		i;
	int		new_i;

	count_ltype = get_num_of_ltype(str);
	new_str = (char *)ft_calloc(ft_strlen(str) + count_ltype * 2 + 1, \
		sizeof(char));
	if (!new_str)
		exit(1);
	new_i = 0;
	i = -1;
	while (++i < (int)ft_strlen(str) + 1)
	{
		if (str[i] == ' ')
		{
			if (new_str[new_i - 1] != ' ')
				new_str[new_i++] = ' ';
			while (str[i] == ' ')
				i++;
		}
		str_addback_ltype(&new_str, str, &i, &new_i);
	}
	free(str);
	return (new_str);
}
