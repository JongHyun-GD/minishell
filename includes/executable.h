/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:25:11 by dason             #+#    #+#             */
/*   Updated: 2021/12/15 17:25:12 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTABLE_H
# define EXECUTABLE_H

# include "info.h"
# include "list_node.h"
# include "minishell.h"

# include <stdio.h>
# include <sys/wait.h>

int		executable(t_list *work_list, char **argv, char **envp, t_info *info);

#endif
