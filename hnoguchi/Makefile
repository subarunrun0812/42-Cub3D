NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES_DIR = ./srcs
LIBFT_DIR = ./srcs/libft

SOURCES = $(SOURCES_DIR)/main.c\
		  $(SOURCES_DIR)/read_map.c\
		  $(SOURCES_DIR)/print_error.c\
		  $(GNL_DIR)/get_next_line.c\
		  $(GNL_DIR)/get_next_line_utils.c\

GNL_DIR = ./srcs/get_next_line
GNL = $(GNL_DIR)/get_next_line.a

INCLUDE = -I include -I $(LIBFT_DIR) -I $(GNL_DIR)

OBJS = $(patsubst %.c,%.o,$(SOURCES)) # ここを変更

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

LIBFT = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# norm:
	# norminette srcs/*.c srcs/*/*.c includes/*.h


funcs:
	nm -u cub3D | \
	grep -v "\(open\|close\|read\|write\|printf\|malloc\|free\|perror\|strerror\|exit\)" | \
	grep -v '\w\+\s_\w\+'

# NAME = cub3D
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# # LIBS = -Lminilibx-linux -lmlx_Linux -L/usr/X11R6/lib -lXext -lX11
# SOURCES_DIR = ./srcs
# LIBFT_DIR = ./srcs/libft

# SOURCES = $(SOURCES_DIR)/main.c\
# 		  $(SOURCES_DIR)/read_map.c\
# 		  $(SOURCES_DIR)/print_error.c\
# 		  $(GNL_DIR)/get_next_line.c\
# 		  $(GNL_DIR)/get_next_line_utils.c\

# GNL_DIR			= ./get_next_line
# GNL				= $(GNL_DIR)/get_next_line.a

# # MINILIBX_DIR	= ./minilibx-linux
# # MINILIBX		= $(MINILIBX_DIR)/libmlx.a
# INCLUDE			= -I include -I $(LIBFT_DIR)
# # INCLUDE			= -I minilibx-linux -I /usr/X11R6/inxlude

# OBJS = $(SOURCES:.c=.o)

# LIBFT = -L$(LIBFT_DIR) -lft

# all: $(NAME)

# $(NAME) : $(OBJS) $(MINILIBX)
# 	$(MAKE) -c $(LIBFT_DIR)
# 	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) -o $(NAME)
# # $(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)

# # $(MINILIBX) :
# # 	make -C $(MINILIBX_DIR)

# clean:
# 	rm -f $(OBJS)
# 	$(MAKE) -C $(LIBFT_DIR) clean

# fclean : clean
# 	rm -f $(NAME)
# 	$(MAKE) -C $(LIBFT_DIR) fclean
# # make -C $(MINILIBX_DIR)  clean 

# re: fclean all
