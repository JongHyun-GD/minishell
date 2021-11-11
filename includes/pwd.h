/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:35 by hyun              #+#    #+#             */
/*   Updated: 2021/11/11 09:29:44 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PWD_H
# define PWD_H

# include "list_node.h"
# include <unistd.h>
# include <stdio.h>

# define PATH_LENGTH 1024

int	pwd(void);

#endif
