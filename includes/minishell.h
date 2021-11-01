#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

t_node	*ft_create_node(int n_type, char *data);
t_list	*ft_create_list(int l_type, int size);

#endif
