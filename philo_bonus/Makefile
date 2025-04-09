# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 22:12:56 by sngantch          #+#    #+#              #
#    Updated: 2025/04/08 22:16:49 by sngantch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus 


CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main_bonus.c utils_bonus.c init_bonus.c  parsing_bonus.c routine_bonus.c

OBJS  = $(SRCS:.c=.o)

RM  = rm -fr


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread
	
clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus