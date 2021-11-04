/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:35:39 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/04 14:07:49 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

bool	has_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}

bool	has_same_envp_key(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
	{
		if (a[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

char	**dup_envp(char **envp)
{
	int		i;
	char	**my_envp;

	i = -1;
	while (envp[++i])
		;
	my_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (my_envp == NULL)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		my_envp[i] = ft_strdup(envp[i]);
	}
	my_envp[i] = NULL;
	return (my_envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		free(envp[i]);
	}
	free(envp);
}
