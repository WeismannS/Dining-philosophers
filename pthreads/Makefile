NAME= philo
SOURCES= Philos.c util.c main.c ft_atoi.c
OBJECTS= $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -pthread -g3

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f philo

re: fclean all

.PHONY: all bonus clean fclean re
