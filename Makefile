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
CFLAGS = -Wall -Wextra -Werror -Iincludes
AR = ar rcs
RM = rm -f

SRCS_DIR = srcs/
OBJS_DIR = obj/
HEADER = includes/philo.h

FILES = data_init \
		dinner \
		getters_setters \
		grim_reaper \
		main \
		parser \
		safe_functions \
		synchro \
		utils \
		write

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
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
