CC = cc
SRCS = main.c time.c write.c parse.c monitoring.c init_ph.c dinner.c syncro.c
CFLAGS= -Wall -Wextra -Werror -pthread

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

.SECONDARY : $(OBJS)