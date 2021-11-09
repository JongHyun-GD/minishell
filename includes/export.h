#ifndef EXPORT_H
# define EXPORT_H

# include "list_node.h"
# include "info.h"
# include "envp.h"
# include "../libft/includes/libft.h"
# include <stdbool.h>

int	export(t_list *list, t_info *info);
int	remove_envp_index(int idx, char **envp, t_info *info);
int	remove_envp(char *data, char **envp, t_info *info);

#endif
