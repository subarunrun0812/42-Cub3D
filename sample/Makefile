# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:31:13 by takuokam          #+#    #+#              #
#    Updated: 2023/06/08 15:38:00 by susasaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := sample_fps
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
INC		:=	-I inc/
SRC_DIR	:=	src/
OBJ_DIR	:=	objs/

SRCS_NAME	:= main.c raycasting.c
OBJS_NAME	:= main.o raycasting.o

SRCS	:=	$(addprefix $(SRC_DIR), $(SRCS_NAME))
OBJS	:=	$(addprefix $(OBJ_DIR), $(OBJS_NAME))

LIBMLX := ./libmlx.a
LIBFLAGS := -L/usr/X11R6/lib -lmlx -lX11 -lXext -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(INC) -o $(NAME) $(SRCS) $(LIBMLX) $(LIBFLAGS)

# $(CFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
