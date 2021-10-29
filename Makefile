CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -lreadline

INC_LINK	= -I./includes/
NAME		= minishell
SRC_DIR		= ./src/
C_FILES		= main.c

SRCS		= $(addprefix $(SRC_DIR), $(C_FILES))
OBJS		= $(SRCS:.c=.o)

%.o			: %.c
	gcc -c $(CFLAGS) $(INC_LINK) $< -o $@

all			: $(NAME)

$(NAME)	: $(OBJS)
	gcc $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME) 

clean		:
	rm -f $(OBJS)

fclean		:
	rm -f $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
