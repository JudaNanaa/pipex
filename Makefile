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

C_FLAGS = -Wall -Wextra -Werror -g3 

SRCS = $(addprefix mandatory_part/, main.c  utils.c path.c)

OBJS = $(SRCS:.c=.o)

NAME = pipex

LIBFT = libft.a

$(LIBFT):
	make -C ./libft

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -I includes -L ./libft -lft -o $@

%.o : %.c
	$(CC) $(C_FLAGS) -c  $^ -o $@

clean :
	rm -rf $(OBJS)
	make clean -C ./libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C ./libft

re : fclean all

.PHONY : all clean fclean re
