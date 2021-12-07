/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:35:52 by hyun              #+#    #+#             */
/*   Updated: 2021/12/07 13:08:33 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_redirect_l(t_list *list, t_info *info)
{
	int		fd;
	char	*data;
	char	ch;
	int		len;

	if (list->next)
	{
		fd = open(list->next->start_node->data, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: no such file or directory: %s",
				list->next->start_node->data);
			return;
		}
		info->has_redirect_l1 = true;
		len = 0;
		while (read(fd, &ch, 1) > 0)
			len++;
		close(fd);
		fd = open(list->next->start_node->data, O_RDONLY);
		data = (char *)malloc(sizeof(char) * len + 1);
		read(fd, data, len);
		info->l1_data = data;
		info->l1_data[len + 1] = 0;
		info->l1_data_len = len;
		close(fd);
	}
}

void	handle_redirect_r(t_list *list, t_info *info)
{
	info->has_redirect_r1 = true;
	if (list->next)
		info->r1_path = ft_strdup(list->next->start_node->data);
}

void	handle_redirect_r2(t_list *list, t_info *info)
{
	info->has_redirect_r2 = true;
	if (list->next)
		info->r2_path = ft_strdup(list->next->start_node->data);
}

void	handle_redirect(t_list *list, t_info *info)
{
	if (list->l_type != LTYPE_COMMAND)
		return ;
	list = list->next;
	while (list)
	{
		if (list->l_type == LTYPE_PIPE)
		{
			pipe(info->pipe_in);
			info->has_pipe_in = true;
			break ;
		}
		if (list->l_type == LTYPE_REDIRECT_L)
		{
			handle_redirect_l(list, info);
		}
		if (list->l_type == LTYPE_REDIRECT2_L)
		{
			// TODO: << 구현
			// handle_redirect2_l();
		}
		if (list->l_type == LTYPE_REDIRECT_R)
		{
			handle_redirect_r(list, info);
		}
		if (list->l_type == LTYPE_REDIRECT2_R)
		{
			handle_redirect_r2(list, info);
		}
		if (list->l_type == LTYPE_COMMAND)
			break ;
		list = list->next;
	}
}
