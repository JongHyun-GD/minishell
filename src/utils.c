/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:51:36 by dason             #+#    #+#             */
/*   Updated: 2021/11/22 11:10:55 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_double_pointer(char ***s)
{
	int		i;

	i = -1;
	while ((*s)[++i])
	{
		free((*s)[i]);
		(*s)[i] = NULL;
	}
	free(*s);
	*s = NULL;
}

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
