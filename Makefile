# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atran <atran@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 17:50:04 by atran             #+#    #+#              #
#    Updated: 2025/02/20 17:42:54 by atran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = fdf.c check_file_and_create_map.c create_grid.c

MLX_DIR = MLX42
MLX_REPO = git@github.com:codam-coding-college/MLX42.git
MLX_BUILD_DIR = MLX42/build
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a
MLXFLAGS = -L$(MLX_BUILD_DIR) -lmlx42 -ldl -lglfw -pthread -lm

OBJS = $(SRCS:%.c=%.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all : $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@cd $(MLX_DIR) && cmake -B build && cd ../..

$(OBJS): %.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
		make all -C Libft
		make all -C MLX42/build
		cc $(OBJS) -LLibft -lft $(MLXFLAGS) -o $(NAME)

clean :
		$(RM) $(OBJS)
		make clean -C Libft
		rm -rf $(MLX_DIR)

fclean : clean
		$(RM) $(NAME)
		make fclean -C Libft
		rm -rf $(MLX_DIR)

re : fclean all

.PHONY: all clean fclean re
