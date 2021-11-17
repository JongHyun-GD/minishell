/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:58:45 by dason             #+#    #+#             */
/*   Updated: 2021/11/17 15:58:45 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	make_list_quote(t_list **list, char *s)
{
	t_list	*new_list;
	int		i;
	int		tmp_i;

	i = 0;
	while (s[i])
	{
		if (i == 0 || get_l_type(&s[i - 1]) != LTYPE_COMMAND)
		{
			tmp_i = i;
			while (s[tmp_i] && get_l_type(&s[tmp_i]) == LTYPE_COMMAND)
				tmp_i++;
			new_list = ft_create_list(LTYPE_COMMAND, \
				ft_create_node(NTYPE_COMMAND, ft_substr(&s[i], 0, tmp_i - i)));
			if (i == 0)
				*list = new_list;
			else
				ft_lstadd_back(*list, new_list);
			i = tmp_i;
		}
		else if (get_l_type(&s[i]) != LTYPE_COMMAND)
			ft_lstadd_back(*list, ft_create_list(get_l_type(&s[i++]), NULL));
	}
}

void	make_list_no_quote(t_list **list, char **lexer)
{
	t_list	*new_list;
	int		i;

	i = -1;
	while (lexer[++i])
	{
		if (i == 0 || get_l_type(lexer[i - 1]) != LTYPE_COMMAND)
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
