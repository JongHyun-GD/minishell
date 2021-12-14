/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:35:07 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/13 18:47:41 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cd.h"

char	*make_path(char **split_path)
{
	char	*path;
	size_t	total_size;
	int		i;
	int		it;
	int		p_i;

	total_size = 0;
	i = -1;
	while (split_path[++i])
		total_size += ft_strlen(split_path[i]);
	path = (char *)ft_calloc(sizeof(char) * (total_size + i), 1);
	i = -1;
	p_i = -1;
	while (split_path[++i])
	{
		it = -1;
		while (split_path[i][++it])
			path[++p_i] = split_path[i][it];
		if (split_path[i + 1])
			path[++p_i] = '/';
		free(split_path[i]);
	}
	free(split_path);
	return (path);
}

char	**make_split_path(char *path, t_info *info)
{
	char	**split_path;

	split_path = ft_split(path, '/');
	if (split_path[0][0] == '~' && ft_strlen(split_path[0]) == 1)
	{
		free(split_path[0]);
		split_path[0] = dup_envp_value("HOME", info->envp);
	}
	return (split_path);
}

int	cd(t_list *list, t_info *info)
{
	int		flag;
	char	*path;

	if (list->start_node->next == NULL)
	{
		path = dup_envp_value("HOME", info->envp);
	}
	else
	{
		path = list->start_node->next->data;
		path = make_path(make_split_path(path, info));
	}
	flag = chdir(path);
	if (flag == -1 && list->start_node->next != NULL)
		printf("minishell: cd: %s: No such file or directory\n",
			list->start_node->next->data);
	else if (flag == -1 && list->start_node->next == NULL)
		printf("minishell: cd: No home directory\n");
	free(path);
	return (0);
}
