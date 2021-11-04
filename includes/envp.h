#ifndef ENVP_H
# define ENVP_H

# include <stdlib.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

char	**dup_envp(char **envp);
void	free_envp(char **envp);
bool	has_same_envp_key(char *a, char *b);
bool	has_equal(char *str);

#endif
