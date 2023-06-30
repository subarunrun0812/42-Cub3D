NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -Lmlx -lmlx -framework OpenGL -framework AppKit
SOURCES_DIR = ./srcs
LIBFT_DIR = ./srcs/libft
MAPS_DIR = $(SOURCES_DIR)/maps
RAYCASTING_DIR = $(SOURCES_DIR)/raycasting
WINDOW_DIR = $(SOURCES_DIR)/window
PLAYER_DIR = $(SOURCES_DIR)/player
MINIMAP_DIR = $(SOURCES_DIR)/minimap

# SOURCES = $(RAYCASTING_DIR)/raycaster_flat.c
# SOURCES = $(RAYCASTING_DIR)/xpm_image.c
# SOURCES = $(RAYCASTING_DIR)/raycaster_textured.c
# SOURCES = $(RAYCASTING_DIR)/raycaster_xpm_textured.c
# SOURCES = $(RAYCASTING_DIR)/raycaster_floor.c

SOURCES = $(SOURCES_DIR)/main.c\
          $(SOURCES_DIR)/free.c\
          $(SOURCES_DIR)/init.c\
          $(SOURCES_DIR)/print_error.c\
          $(SOURCES_DIR)/read_texture.c\
          $(SOURCES_DIR)/assign_to_structure.c\
          $(SOURCES_DIR)/assign_to_structure_floor_celling.c\
          $(SOURCES_DIR)/assign_to_structure_nswe.c\
          $(MAPS_DIR)/read_map.c\
          $(MAPS_DIR)/get_map_data.c\
          $(MAPS_DIR)/check_map_wall.c\
          $(MAPS_DIR)/check_only_one_nswe.c\
          $(MINIMAP_DIR)/minimap.c\
          $(MINIMAP_DIR)/central_map.c\
          $(MINIMAP_DIR)/updata_pos_map.c\
          $(PLAYER_DIR)/coordinates.c\
          $(RAYCASTING_DIR)/raycasting.c\
          $(RAYCASTING_DIR)/calculate_nearest_axis.c\
          $(RAYCASTING_DIR)/draw_line.c\
          $(RAYCASTING_DIR)/my_mlx_pixel_put_line.c\
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

VPATH = $(SOURCES_DIR):$(MAPS_DIR):$(RAYCASTING_DIR):$(GNL_DIR) \
		$(WINDOW_DIR):$(PLAYER_DIR):$(MINIMAP_DIR)

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
