/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:15:21 by hyun              #+#    #+#             */
/*   Updated: 2021/12/13 10:16:17 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	postprocess(t_info *info)
{
	if (info->has_pipe_in)
	{
		close(info->pipe_in[WRITE_END]);
		info->has_pipe_in = false;
	}
	if (info->has_redirect_l1)
		info->has_redirect_l1 = false;
	if (info->has_redirect_l2)
		info->has_redirect_l2 = false;
	if (info->has_redirect_r1)
		info->has_redirect_r1 = false;
	if (info->has_redirect_r2)
		info->has_redirect_r2 = false;
}
