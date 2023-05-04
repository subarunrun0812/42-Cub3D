NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES_DIR = ./srcs
LIBFT_DIR = ./srcs/libft
MAPS_DIR = $(SOURCES_DIR)/maps
RAYCASTING_DIR = $(SOURCES_DIR)/raycasting

SOURCES = $(SOURCES_DIR)/main.c\
          $(MAPS_DIR)/read_map.c\
          $(MAPS_DIR)/get_map_data.c\
          $(SOURCES_DIR)/free.c\
          $(SOURCES_DIR)/init.c\
          $(SOURCES_DIR)/print_error.c\
          $(GNL_DIR)/get_next_line.c\
          $(GNL_DIR)/get_next_line_utils.c\

GNL_DIR = ./srcs/get_next_line
GNL = $(GNL_DIR)/get_next_line.a

INCLUDE = -I include -I $(LIBFT_DIR) -I $(GNL_DIR)

# makeがファイルを検索する際に使用するディレクトリのリストを指定するための変数
VPATH = $(SOURCES_DIR):$(MAPS_DIR):$(RAYCASTING_DIR):$(GNL_DIR)

OBJS_DIR = objs
# addprefixの構成[$(addprefix prefix, list)]
# prefix: 追加する接頭辞
# list: 接頭辞を追加する文字列のリスト
# notdir 関数は、引数で与えられたパスのうち、ディレクトリ部分を取り除き、ファイル名のみを返します。
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SOURCES:.c=.o)))

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

LIBFT = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
