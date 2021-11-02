#ifndef LIST_H
# define LIST_H

# define NTYPE_NONE 0
# define NTYPE_COMMAND 1
# define NTYPE_FLAG 2
# define NTYPE_DATA 3

# define LTYPE_NONE 0
# define LTYPE_COMMAND 1
# define LTYPE_PIPE 2
# define LTYPE_SEMI_COLON 3
# define LTYPE_REDIRECT 4

typedef struct	s_node
{
	int				n_type;
	char			*data;
	struct s_node	*next;
}					t_node;

typedef struct s_list
{
	int				l_type;
	struct s_node	*start_node;
	struct s_list	*next;
}					t_list;

#endif
