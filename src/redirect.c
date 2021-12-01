/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:35:52 by hyun              #+#    #+#             */
/*   Updated: 2021/12/01 14:04:03 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void swap_pipe(t_info *info)
{
	int	temp[2];

	temp[0] = info->pipe_in[0];
	temp[1] = info->pipe_in[1];
	info->pipe_in[0] = info->pipe_out[0];
	info->pipe_in[1] = info->pipe_out[1];
	info->pipe_out[0] = temp[0];
	info->pipe_out[1] = temp[1];
}

void handle_redirect(t_list *list, t_info *info)
{
	printf("info: %p\n", info);
	if (list->l_type != LTYPE_COMMAND)
		return;
	list = list->next;
	while (list)
	{
		if (list->l_type == LTYPE_PIPE)
		{
			pipe(info->pipe_in);
			info->has_pipe_in = true;
			break;
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
