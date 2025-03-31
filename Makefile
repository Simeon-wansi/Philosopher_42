
NAME = philo

SRCS =    init.c	main.c	monitor.c  parsing.c   routine.c     thread_managing.c       utils.c

OBJS = $(SRCS:.c=.o)

CC =  cc
CFLAGS = -Wall -Wextra -Werror -pthread

RM =  rm -f


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS)  -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean 
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean