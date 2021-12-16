/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:57:50 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/15 18:16:46 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		return ;
	}
	else if (sig == SIGINT)
	{
		exit(STAT_CTRL_C);
	}
}

void	set_signal_child(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_stty(t_info *info)
{
	tcgetattr(STDOUT_FILENO, &info->orig_term);
	tcgetattr(STDOUT_FILENO, &info->new_term);
	info->new_term.c_lflag &= (~ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &info->new_term);
}
