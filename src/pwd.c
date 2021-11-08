/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:25:28 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/08 10:22:14 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pwd.h"

int	pwd(void)
{
	char	path[PATH_LENGTH];

	printf("%s\n", getcwd(path, PATH_LENGTH));
	return (0);
}
