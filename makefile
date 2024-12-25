CC = cc
SRCS = main.c setter_getter.c time.c write.c parse.c monitoring.c clean.c
CFLAGS= -Wall -Wextra -Werror -fsanitize=address -g

NAME = philo

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
