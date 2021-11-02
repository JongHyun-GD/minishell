/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:56:06 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/02 14:25:12 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		printf("Error: Invalid arguments\n");
		return (-1);
	}
	argv = 0;
	while (*envp)
	{
		if (ft_strlen(*envp) == 0)
			break ;
		printf("%s\n", *envp);
		envp++;
	}
}
