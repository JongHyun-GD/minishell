TARGET = minishell
SRCS =	main.c
OBJS =	$(SRCS:.c=.o)
CC =	gcc
CF =	-Wall -Wextra -Werror -Iincludes -lreadline 

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CF) $^ -o $@

%.o : %.c
	$(CC) $< -c

clean :
	rm -f *.o

fclean : clean
	rm -f $(TARGET)

re : fclean all

bonus : all

t : all
	./minishell

.PHONY = all clean fclean re bonus
