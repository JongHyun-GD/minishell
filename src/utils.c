/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:51:36 by dason             #+#    #+#             */
/*   Updated: 2021/11/29 17:27:47 by dason            ###   ########.fr       */
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
