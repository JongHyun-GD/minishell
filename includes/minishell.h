#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"
# include "../libft/includes/libft.h"
# include "../get_next_line.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_info
{
	char	**env;
}			t_info;

#endif
