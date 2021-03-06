# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hivian <hivian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 10:17:30 by hivian            #+#    #+#              #
#    Updated: 2018/05/09 15:20:49 by lnieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= scop
CC 	 		= clang -Wall -Wextra -Werror


LIBS		= -L libft/ -lft -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

SRC  		= main.c \
			parser.c \
			face_parsing.c \
			vertex_parsing.c \
			display.c \
			matrices.c \
			key_handling.c \
			colors.c \
			init.c \
			shaders.c \
			shader_data.c \

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
