# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 11:52:57 by fde-souz          #+#    #+#              #
#    Updated: 2018/02/12 17:47:10 by vgauther         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

NAME = wolf3d

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LFT_PATH = ./libft/
MLX_PATH = ./minilibx_macos/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_NAME = wolf3d.h

SRC_NAME =	hud.c \
			main.c \
			error.c \
			image.c  \
			parser.c  \
			radian.c   \
			translate.c \
			intersection.c \
			load_texture.c \
			child.c \
			file_image.c \
			hook.c \
			draw.c

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@gcc ./Mke_src/loup.c -lm -L $(LFT_PATH) -lft
	@./a.out
	@rm a.out
	@$(CC) -o $(NAME) $(OBJ) -lm -L $(LFT_PATH) -lft -lm -L $(MLX_PATH) -lmlx -lm -framework OpenGL -framework AppKit
	@echo "[✓] EXECUTABLE WOLF 3D DONE"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LFT_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C $(LFT_PATH) fclean
	@rm -f $(NAME)
clean_o:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re:
	@make fclean
	@make all
