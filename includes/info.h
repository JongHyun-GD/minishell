/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:26 by hyun              #+#    #+#             */
/*   Updated: 2021/12/07 12:52:23 by jongpark         ###   ########.fr       */
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
	bool			has_redirect_r1;
	bool			has_redirect_r2;
	bool			has_redirect_l1;
	char			*r1_path;
	char			*r2_path;
	char			*l1_data;
	int				l1_data_len;
}			t_info;

#endif
