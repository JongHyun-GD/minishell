CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -lreadline

INC_LINK	= -I./includes/

LIBFT_NAME      = libft.a
LIBFT_DIR       = ./libft/
LIBFT           = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

NAME		= minishell
SRC_DIR		= ./src/
C_FILES		= get_next_line.c		\
			  get_next_line_utils.c	\
			  env.c \
			  main.c

SRCS		= $(addprefix $(SRC_DIR), $(C_FILES))
OBJS		= $(SRCS:.c=.o)

%.o			: %.c
	gcc -c $(CFLAGS) $(INC_LINK) $< -o $@

all			: $(LIBFT) $(NAME)

$(NAME)	: $(LIBFT) $(OBJS)
	gcc $(CFLAGS)  $(LFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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
