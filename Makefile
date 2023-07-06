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

SOURCES = $(SOURCES_DIR)/main.c\
          $(SOURCES_DIR)/free.c\
          $(SOURCES_DIR)/init.c\
          $(SOURCES_DIR)/print_error.c\
          $(FILE_READ_DIR)/assign_to_structure.c\
          $(FILE_READ_DIR)/assign_to_structure_floor_celling.c\
          $(FILE_READ_DIR)/assign_to_structure_nswe.c\
          $(FILE_READ_DIR)/assign_to_structure_rgb.c\
          $(FILE_READ_DIR)/read_file.c\
          $(FILE_READ_DIR)/get_data_file.c\
          $(FILE_READ_DIR)/check_map_wall.c\
          $(FILE_READ_DIR)/check_only_one_nswe.c\
          $(FILE_READ_DIR)/read_texture.c\
          $(MINIMAP_DIR)/minimap.c\
          $(MINIMAP_DIR)/central_map.c\
          $(MINIMAP_DIR)/player_coordinates.c\
          $(MINIMAP_DIR)/updata_pos_map.c\
		  $(RAYCASTING_DIR)/clean_image.c\
		  $(RAYCASTING_DIR)/draw_wall.c\
		  $(RAYCASTING_DIR)/init_nswe_direction.c\
		  $(RAYCASTING_DIR)/put_texture_ceil.c\
		  $(RAYCASTING_DIR)/set_draw_wall_data.c\
		  $(RAYCASTING_DIR)/create_xpm_textures.c\
		  $(RAYCASTING_DIR)/exit_mlx.c\
		  $(RAYCASTING_DIR)/key_action.c\
		  $(RAYCASTING_DIR)/put_texture_floor.c\
		  $(RAYCASTING_DIR)/try_draw_texture_floor_and_ceil.c\
		  $(RAYCASTING_DIR)/destruct_raycasting.c\
		  $(RAYCASTING_DIR)/get_nearest_axis.c\
		  $(RAYCASTING_DIR)/my_mlx_pixel_put_line.c\
		  $(RAYCASTING_DIR)/raycasting.c\
		  $(RAYCASTING_DIR)/draw_color_floor_and_ceil.c\
		  $(RAYCASTING_DIR)/mouse_action.c\
		  $(RAYCASTING_DIR)/set_draw_texture_data.c\
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
