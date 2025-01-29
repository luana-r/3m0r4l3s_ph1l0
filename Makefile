# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emorales <emorales@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 14:51:00 by emorales          #+#    #+#              #
#    Updated: 2025/01/28 17:41:42 by emorales         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes
RM = rm -f

SRCS_DIR = srcs
OBJS_DIR = obj
HEADER = philo.h

SRCS = $(shell find . -type f -name "*.c")
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

$(OBJS_DIR)/%.o: %.c $(HEADER)
		@mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -pthread

clean:
		$(RM) -r $(OBJS_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
