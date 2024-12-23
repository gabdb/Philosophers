NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS =	main.c \
		init.c \
		routine.c \
		utils.c \
		free.c \
		parsing.c \
		routine_utils.c \
		fork.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re