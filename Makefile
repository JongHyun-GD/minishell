CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lreadline -L /usr/local/Cellar/readline/8.1.1/lib

INC_LINK	= -I./includes/ -I/usr/local/Cellar/readline/8.1.1/include

LIBFT_NAME      = libft.a
LIBFT_DIR       = ./libft/
LIBFT           = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

NAME		= minishell
SRC_DIR		= ./src/
C_FILES		= cd.c							\
			  echo.c						\
			  env.c							\
			  envp.c 						\
			  execute_builtin.c				\
			  execute_non_builtin.c			\
			  export.c 						\
			  free.c						\
			  get_next_line.c				\
			  get_next_line_utils.c			\
			  get_user_input.c				\
			  init.c						\
			  list_node_utils.c				\
			  main.c						\
			  parser.c						\
			  parser_handling_exception.c	\
			  parser_make_list.c			\
			  parser_organize_node.c		\
			  parser_organize_str.c			\
			  parser_utils.c				\
			  pwd.c 						\
			  redirect.c					\
			  set_signal.c					\
			  unset.c 						\
			  utils.c						\
			  preprocess.c					\
			  preprocess2.c					\
			  postprocess.c					\
			  utils.c

SRCS		= $(addprefix $(SRC_DIR), $(C_FILES))
OBJS		= $(SRCS:.c=.o)

%.o			: %.c
	gcc -c $(CFLAGS) $(INC_LINK) $< -o $@

all			: $(LIBFT) $(NAME)

$(NAME)	: $(LIBFT) $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)

$(LIBFT)	:
	@make all -C $(LIBFT_DIR)

clean		:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean		:
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
