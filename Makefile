# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 17:26:32 by madamou           #+#    #+#              #
#    Updated: 2024/05/19 19:56:48 by madamou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -Wall -Wextra -Werror -g3 -no-pie

SRCS = $(addprefix mandatory_part/, main.c  utils.c path.c)

OBJS = $(SRCS:.c=.o)

NAME = pipex

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(C_FLAGS) $^ -I includes -L lib -lft -lftprintf -lget_next_line -o $@

%.o : %.c
	$(CC) $(C_FLAGS) -c  $^ -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
