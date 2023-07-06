NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror
LIBS = -Lmlx -lmlx -framework OpenGL -framework AppKit
SOURCES_DIR = ./srcs
LIBFT_DIR = ./srcs/libft
FILE_READ_DIR = $(SOURCES_DIR)/file_read
RAYCASTING_DIR = $(SOURCES_DIR)/raycasting
WINDOW_DIR = $(SOURCES_DIR)/window
MINIMAP_DIR = $(SOURCES_DIR)/minimap

# SOURCES = $(RAYCASTING_DIR)/raycaster_flat.c
# SOURCES = $(RAYCASTING_DIR)/xpm_image.c
# SOURCES = $(RAYCASTING_DIR)/raycaster_textured.c
# SOURCES = $(RAYCASTING_DIR)/raycaster_xpm_textured.c
# SOURCES = $(RAYCASTING_DIR)/raycaster_floor.c
# SOURCES = $(RAYCASTING_DIR)/raycasting_hnoguchi.c

SOURCES = $(SOURCES_DIR)/main.c\
          $(SOURCES_DIR)/free.c\
          $(SOURCES_DIR)/init.c\
          $(SOURCES_DIR)/print_error.c\
          $(FILE_READ_DIR)/assign_to_structure_rgb.c\
          $(FILE_READ_DIR)/assign_to_structure.c\
          $(FILE_READ_DIR)/read_file.c\
          $(FILE_READ_DIR)/check_only_one_nswe.c\
          $(FILE_READ_DIR)/get_data_file.c\
          $(FILE_READ_DIR)/handle_texture.c\
          $(FILE_READ_DIR)/mapdata_check.c\
          $(FILE_READ_DIR)/mapdata_stradd.c\
          $(FILE_READ_DIR)/mapdata_utils.c\
          $(FILE_READ_DIR)/read_texture.c\
          $(FILE_READ_DIR)/rgb_utils.c\
          $(FILE_READ_DIR)/utils.c\
          $(MINIMAP_DIR)/central_map_fov.c\
          $(MINIMAP_DIR)/central_map.c\
          $(MINIMAP_DIR)/map_utils.c\
          $(MINIMAP_DIR)/corner_map.c\
          $(MINIMAP_DIR)/minimap.c\
          $(MINIMAP_DIR)/player_coordinates.c\
          $(RAYCASTING_DIR)/raycasting_hnoguchi.c\
          $(WINDOW_DIR)/close_window.c\
          $(WINDOW_DIR)/my_mlx_pixel_put.c\
          $(WINDOW_DIR)/new_window.c\
          $(GNL_DIR)/get_next_line.c\
          $(GNL_DIR)/get_next_line_utils.c

GNL_DIR = ./srcs/get_next_line
GNL = $(GNL_DIR)/get_next_line.a

MINILIBX_DIR = ./mlx
MINILIBX	 = $(MINILIBX_DIR)/libmlx.a

INCLUDE = -I include -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MINILIBX_DIR)

VPATH = $(SOURCES_DIR):$(FILE_READ_DIR):$(RAYCASTING_DIR):$(GNL_DIR) \
		$(WINDOW_DIR):$(MINIMAP_DIR)

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SOURCES:.c=.o)))

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

LIBFT = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(MINILIBX_DIR) :
	make -C $(MINILIBX_DIR)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) $(LIBS) -o $(NAME)


clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(MINILIBX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
