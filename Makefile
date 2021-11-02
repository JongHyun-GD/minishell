CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -lreadline

INC_LINK	= -I./includes/

LIBFT_NAME      = libft.a
LIBFT_DIR       = ./libft/
LIBFT           = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

NAME		= minishell
SRC_DIR		= ./src/
C_FILES		= main.c \
				envp.c \
				get_next_line.c \
				get_next_line_utils.c

SRCS		= $(addprefix $(SRC_DIR), $(C_FILES))
OBJS		= $(SRCS:.c=.o)

ENV			= env
ENV_C_FILES	= env.c
ENV_SRCS	= $(addprefix $(SRC_DIR), $(ENV_C_FILES))
ENV_OBJS	= $(ENV_SRCS:.c=.o)

%.o			: %.c
	gcc -c $(CFLAGS) $(INC_LINK) $< -o $@

all			: $(LIBFT) $(NAME)

$(NAME)	: $(LIBFT) $(OBJS) $(ENV_OBJS)
	gcc $(CFLAGS) $(LFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	gcc $(CFLAGS) $(LFLAGS) $(ENV_OBJS) $(LIBFT) -o $(ENV)

$(LIBFT)	:
	@make all -C $(LIBFT_DIR)

clean		:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)
	rm -f $(ENV_OBJS)

fclean		: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -f $(ENV)

re			: fclean all

.PHONY		: all clean fclean re
