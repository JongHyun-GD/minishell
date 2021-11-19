/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:26 by hyun              #+#    #+#             */
/*   Updated: 2021/11/16 14:22:54 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include <termios.h>

typedef struct s_info
{
	char			**envp;
	struct termios	orig_term;
	struct termios	new_term;
}			t_info;

#endif
