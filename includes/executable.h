#ifndef EXECUTABLE_H
# define EXCUTABLE_H

# include "info.h"
# include "list_node.h"
# include "minishell.h"

# include <stdio.h>
# include <sys/wait.h>

int		executable(t_list *work_list, char **argv, char **envp, t_info *info);

#endif