###########
# General #
###########

NAME = raycasting
CC = cc
CFLAGS = -Wall -Wextra -Werror
OVERFLOWFLAGS = -g -fsanitize=undefined -fsanitize=integer -fsanitize=address
SOURCES = main.c vector.c ray.c player.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SOURCES:%.c=%.o))
OBJS_DIR = ./objs

#################
# General Rules #
#################

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r *.dSYM
	$(RM) -r $(OBJS_DIR)

.PHONY: fclean
fclean : clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: vector
vector: CFLAGS += -DVECTOR
vector: re

.PHONY: ray
ray: CFLAGS += -DRAY
ray: re
