/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:35:52 by hyun              #+#    #+#             */
/*   Updated: 2021/11/24 14:47:59 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirect(t_list *list, t_info *info)
{
	if (list->l_type != LTYPE_COMMAND)
		return;
	list = list->next;
	while (list)
	{
		if (list->l_type == LTYPE_PIPE)
		{
			// TODO: | 구현 ex) ls | grep "src"
			pipe(info->pipe);
			info->is_pipe_in = true;
		}
		if (list->l_type == LTYPE_REDIRECT_L)
		{
			// TODO: < 구현
			// handle_redirect_l();
		}
		if (list->l_type == LTYPE_REDIRECT2_L)
		{
			// TODO: << 구현
			// handle_redirect2_l();
		}
		if (list->l_type == LTYPE_REDIRECT_R)
		{
			// TODO: > 구현
			// handle_redirect_r();
		}
		if (list->l_type == LTYPE_REDIRECT2_R)
		{
			// TODO: >> 구현
			// handle_redirect2_r();
		}
		if (list->l_type == LTYPE_COMMAND)
			break ;
		list = list->next;
	}
}
