/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:26 by hyun              #+#    #+#             */
/*   Updated: 2021/11/24 10:08:28 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include <termios.h>
# include <stdbool.h>

typedef struct s_info
{
	char			**envp;
	struct termios	orig_term;
	struct termios	new_term;
	int				pipe[2];
	bool			is_pipe_in;
	bool			is_pipe_out;
}			t_info;

#endif
