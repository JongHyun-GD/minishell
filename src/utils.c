/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:51:36 by dason             #+#    #+#             */
/*   Updated: 2021/12/13 09:47:41 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_blank(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			return (false);
	}
	return (true);
}

bool	is_valid_input(char *str)
{
	if (str == NULL)
	{
		printf("\n");
		return (false);
	}
	if (ft_strlen(str) == 0 || is_blank(str))
	{
		free(str);
		return (false);
	}
	return (true);
}

void	swap_pipe(t_info *info)
{
	int	temp[2];

	temp[0] = info->pipe_in[0];
	temp[1] = info->pipe_in[1];
	info->pipe_in[0] = info->pipe_out[0];
	info->pipe_in[1] = info->pipe_out[1];
	info->pipe_out[0] = temp[0];
	info->pipe_out[1] = temp[1];
}
