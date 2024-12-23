CC = cc
SRCS = main.c setter_getter.c time.c utils.c write.c
CFLAGS= -Wall -Wextra -Werror 

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
