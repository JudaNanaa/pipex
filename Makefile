# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 17:26:32 by madamou           #+#    #+#              #
#    Updated: 2024/05/17 10:20:19 by madamou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix mandatory_part/, main.c check_if_file_exist.c)

OBJS = $(SRCS:.c=.o)

NAME = pipex

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(C_FLAGS) $^ -o $@

%.o : %.c
	$(CC) $(C_FLAGS) -c $^ -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re