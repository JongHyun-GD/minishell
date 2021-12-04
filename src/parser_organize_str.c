/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_organize_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sondho <sondho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:41:36 by dason             #+#    #+#             */
/*   Updated: 2021/12/04 12:49:31 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	when_char_is_space(char **tmp_str, char *str, int *i, int *new_i)
{
	if (str[*i] == ' ')
	{
		if (*i != 0 && (*tmp_str)[*new_i - 1] != ' ')
			(*tmp_str)[(*new_i)++] = ' ';
		while (str[*i] == ' ')
			(*i)++;
	}
}

static void	str_addback_quote(char **tmp_str, char *str, int *i, int *new_i)
{
	int		quote;

	quote = str[*i];
	while (str[*i])
	{
		(*tmp_str)[(*new_i)++] = str[(*i)++];
		if (str[*i] == quote)
		{
			(*tmp_str)[(*new_i)++] = str[(*i)++];
			break ;
		}
	}
}

static void	str_addback_redirect(char **tmp_str, char *str, int *i, int *new_i)
{
	if (get_ltype(&str[*i]) == LTYPE_REDIRECT2_L || \
		get_ltype(&str[*i]) == LTYPE_REDIRECT2_R)
	{
		if (*new_i != 0 && (*tmp_str)[*new_i - 1] != ' ')
			(*tmp_str)[(*new_i)++] = ' ';
		(*tmp_str)[(*new_i)++] = str[(*i)++];
		(*tmp_str)[(*new_i)++] = str[(*i)++];
		(*tmp_str)[(*new_i)++] = ' ';
	}
	else if (get_ltype(&str[*i]) != LTYPE_COMMAND)
	{
		if (*new_i != 0 && (*tmp_str)[*new_i - 1] != ' ')
			(*tmp_str)[(*new_i)++] = ' ';
		(*tmp_str)[(*new_i)++] = str[(*i)++];
		(*tmp_str)[(*new_i)++] = ' ';
	}
	else if (is_quote(str[*i]))
		str_addback_quote(tmp_str, str, i, new_i);
	else
		(*tmp_str)[(*new_i)++] = str[(*i)++];
}

// TODO: echo a || echo b 처리
char	*organize_input_str(char *str)
{
	char	*tmp_str;
	char	*new_str;
	int		i;
	int		new_i;

	tmp_str = (char *)ft_calloc(\
		ft_strlen(str) + get_num_of_redirect(str) * 2 + 1, sizeof(char));
	if (!tmp_str)
		exit(1);
	new_i = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		when_char_is_space(&tmp_str, str, &i, &new_i);
		str_addback_redirect(&tmp_str, str, &i, &new_i);
	}
	free(str);
	new_str = ft_strtrim(tmp_str, " ");
	free(tmp_str);
	return (new_str);
}
