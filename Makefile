# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 17:26:32 by madamou           #+#    #+#              #
#    Updated: 2024/06/15 16:31:22 by madamou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

OBJS_DIR = .objets/

SRCS_DIR = mandatory_part/

C_FLAGS = -Wall -Wextra -Werror -g3 

SRCS = main.c utils.c path.c pipex.c pipe.c static.c heredoc.c heredoc2.c fork.c

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

DIR_DUP = mkdir -p $(@D)

NAME = pipex

LIBFT = libft.a

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(C_FLAGS) $^ -I includes -L ./libft -lft -o $@

$(LIBFT):
	make -C ./libft

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(DIR_DUP)
	$(CC) $(C_FLAGS) -c  $^ -o $@

clean :
	rm -rf $(OBJS_DIR)
	make clean -C ./libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C ./libft

re : fclean all 

.PHONY : all clean fclean re
