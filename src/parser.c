/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:52:57 by dason             #+#    #+#             */
/*   Updated: 2021/12/09 18:25:50 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	parser_quote(t_list **list, char *str)
{
	t_list	*tmp_list;

	make_list_quote(list, str);
	tmp_list = *list;
	while (tmp_list)
	{
		if (tmp_list->l_type == LTYPE_COMMAND)
			organize_node(tmp_list);
		tmp_list = tmp_list->next;
	}
}

static void	parser_no_quote(t_list **list, char *str)
{
	char	**lexer;

	lexer = ft_split(str, ' ');
	if (!lexer)
		exit(1);
	make_list_no_quote(list, lexer);
	free_double_pointer(&lexer);
}

int	parser(t_list **list, char *str)
{
	t_list	*tmp_list;

	str = organize_input_str(str);
	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
		parser_quote(list, str);
	else
		parser_no_quote(list, str);
	free(str);
	tmp_list = *list;
	if (!parser_handling_exception(tmp_list))
		return (-1);
	return (0);
}
