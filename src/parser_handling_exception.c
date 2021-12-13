/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handling_exception.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:44:28 by dason             #+#    #+#             */
/*   Updated: 2021/12/13 09:44:29 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	print_parse_error_near(int l_type)
{
	if (l_type == 2)
		printf("minishell: syntax error near unexpected token `|'\n");
	if (l_type == 3)
		printf("minishell: syntax error near unexpected token `<'\n");
	if (l_type == 4)
		printf("minishell: syntax error near unexpected token `<<'\n");
	if (l_type == 5)
		printf("minishell: syntax error near unexpected token `>'\n");
	if (l_type == 6)
		printf("minishell: syntax error near unexpected token `>>'\n");
}

int	parser_handling_exception(t_list *list)
{
	while (list)
	{
		if (list->l_type != LTYPE_COMMAND && \
			list->l_type != LTYPE_FILE && \
			list->next->l_type != LTYPE_COMMAND && \
			list->next->l_type != LTYPE_FILE)
		{
			print_parse_error_near(list->next->l_type);
			return (0);
		}
		list = list->next;
	}
	return (1);
}
