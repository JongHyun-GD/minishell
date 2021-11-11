/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:31 by hyun              #+#    #+#             */
/*   Updated: 2021/11/11 09:29:45 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "get_next_line.h"
# include "list_node.h"
# include "info.h"
# include "envp.h"
# include "env.h"
# include "parser.h"
# include "export.h"
# include "unset.h"
# include "pwd.h"
# include "cd.h"
# include "echo.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>

# define PATH_LENGTH 1024
# define LOGO_PATH "etc/logo.txt"
# define LOGO_LENGTH 1024

/*
**	UTILS
*/
void	free_double_pointer(char ***s);

/*
**	EXECUTE
*/
int		execute_non_builtin(char **argv, char **envp);

#endif
