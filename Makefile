# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atran <atran@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 17:50:04 by atran             #+#    #+#              #
#    Updated: 2025/02/17 12:59:56 by atran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = fdf.c

OBJS = $(SRCS:%.c=%.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all : $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
		make all -C Libft
		make -C MLX42/build
		cc $(OBJS) -LLibft -lft -LMLX42/build -lmlx42 -ldl -lglfw -pthread -lm -o $(NAME)

clean :
		$(RM) $(OBJS)
		make clean -C Libft
		make clean -C MLX42/build

fclean : clean
		$(RM) $(NAME)
		make fclean -C Libft
		make clean -C MLX42/build

re : fclean all

.PHONY: all clean fclean re
