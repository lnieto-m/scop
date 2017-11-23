# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hivian <hivian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 10:17:30 by hivian            #+#    #+#              #
#    Updated: 2017/11/23 10:00:15 by lnieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= scop
CC 	 		= clang -Wall -Wextra -Werror


LIBS		= -L libft/ -lft -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

SRC  		= main.c \

OBJ  		= $(SRC:%.c=objs/%.o)


SRC_DIR 	= ./srcs/
INCLUDE_DIR = -I ./incs/ -I libft/includes -I minilibx_macos/

all: objs $(NAME)

objs:
	@mkdir objs

$(NAME): $(OBJ)
	make -C libft/ all
	make -sC ./minilibx_macos/ all
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS) minilibx_macos/mlx_opengl.m

objs/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -o $@ -c $<

clean:
	rm -rf objs
	make clean -C libft/
	make -sC minilibx_macos/ clean

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/
	make -sC minilibx_macos/ clean

re: fclean all

.PHONY: all clean fclean re
