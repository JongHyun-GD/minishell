/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:58:45 by dason             #+#    #+#             */
/*   Updated: 2021/11/26 17:33:25 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	process_when_quote(char *s, int *i, int *len)
{
	int		quote;

	quote = s[*i + *len];
	(*len)++;
	while (s[*i + *len] && s[*i + *len] != quote)
		(*len)++;
}

// TODO: memory leaks
static void	process_the_list(t_list **list, char *s, int *i, int *len)
{
	t_list	*new_list;
	char	*sub_str;

	while (s[*i + *len] && get_l_type(&s[*i + *len]) == LTYPE_COMMAND)
	{
		if (s[*i + *len] == '\"' || s[*i + *len] == '\'')
			process_when_quote(s, i, len);
		(*len)++;
	}
	sub_str = ft_substr(s, *i, *len);
	new_list = ft_create_list(LTYPE_COMMAND, \
			ft_create_node(NTYPE_COMMAND, ft_strtrim(sub_str, " ")));
	if (*i == 0)
		*list = new_list;
	else
		ft_lstadd_back(*list, new_list);
	free(sub_str);
}

void	make_list_quote(t_list **list, char *s)
{
	int		i;
	int		len;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		while (s[i] == ' ')
			i++;
		if (i == 0 || get_l_type(&s[i]) == LTYPE_COMMAND)
		{
			len = 0;
			process_the_list(list, s, &i, &len);
			i += len;
		}
		else if (get_l_type(&s[i]) != LTYPE_COMMAND)
		{
			ft_lstadd_back(*list, ft_create_list(get_l_type(&s[i]), NULL));
			if (get_l_type(&s[i]) == LTYPE_REDIRECT2_L || \
				get_l_type(&s[i]) == LTYPE_REDIRECT2_R)
				i += 2;
			else
				i += 1;
		}
	}
}

void	make_list_no_quote(t_list **list, char **lexer)
{
	t_list	*new_list;
	int		i;

	i = -1;
	while (lexer[++i])
	{
		if (i == 0 || (get_l_type(lexer[i - 1]) != LTYPE_COMMAND && \
			get_l_type(lexer[i]) == LTYPE_COMMAND))
		{
			new_list = ft_create_list(LTYPE_COMMAND, \
					ft_create_node(NTYPE_COMMAND, ft_strdup(lexer[i])));
			if (i == 0)
				*list = new_list;
			else
				ft_lstadd_back(*list, new_list);
		}
		else if (get_l_type(lexer[i]) != LTYPE_COMMAND)
			ft_lstadd_back(*list, ft_create_list(get_l_type(lexer[i]), NULL));
		else
			ft_nodeadd_back(new_list->start_node, \
					ft_create_node(NTYPE_STRING, ft_strdup(lexer[i])));
	}
}
