/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:26 by hyun              #+#    #+#             */
/*   Updated: 2021/12/01 14:07:32 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include <termios.h>
# include <stdbool.h>

# define WRITE_END 1
# define READ_END 0

typedef struct s_info
{
	char			**envp;
	struct termios	orig_term;
	struct termios	new_term;
	int				pipe_in[2];
	int				pipe_out[2];
	bool			has_pipe_in;
}			t_info;

#endif
