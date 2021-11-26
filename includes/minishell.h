/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:31 by hyun              #+#    #+#             */
/*   Updated: 2021/11/26 15:55:37 by dason            ###   ########.fr       */
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
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>

# define PATH_LENGTH 1024
# define LOGO_PATH "etc/logo.txt"
# define LOGO_LENGTH 1024
# define INPUT_BUFFER_SIZE 1024
# define STAT_CTRL_D 3
# define STAT_CTRL_C 4

/*
**	UTILS
*/
void	free_double_pointer(char ***s);
bool	is_blank(char *str);
bool	is_valid_input(char *str);

/*
**	EXECUTE
*/
int		execute_non_builtin(char **argv, char **envp);

/*
**	SIGNAL
*/
void	handle_signal(int sig);
void	set_signal_child(void);
void	set_signal_parent(void);
void	set_stty(t_info *info);

/*
**	INPUT
*/
int		get_exit_result(int stat);
char	*get_user_input(t_info *info);

/*
**	REDIRECT
*/
void	handle_redirect(t_list *list, t_info *info);

#endif
