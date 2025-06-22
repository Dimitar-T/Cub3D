NAME	= cub3D
BONUS_NAME = cub3D_bonus
CFLAGS	= -Wextra -Wall -Wunreachable-code -O3 -g
LIBMLX	= ./MLX42
LIBFT = ./libft

HEADERS = -I ./include -I $(LIBMLX)/include -I $(LIBMLX) $(INCLUDES)
LDFLAGS = -L/usr/local/lib
LDFLAGS += -fsanitize=address
INCLUDES = -I/opt/homebrew/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm $(LIBFT)/libft.a $(LDFLAGS)

SRC_DIR = src
OBJ_DIR = obj
BNS_SRC_DIR = bonus_src
BNS_OBJ_DIR = bonus_obj

SRC	= 	$(SRC_DIR)/main.c $(SRC_DIR)/parsing/file_parsing.c $(SRC_DIR)/parsing/utility.c \
		$(SRC_DIR)/garbage_collector/garbage_collector.c $(SRC_DIR)/parsing/map_parsing.c \
		$(SRC_DIR)/parsing/map_parsing_util.c $(SRC_DIR)/init/init.c $(SRC_DIR)/moves/move_player.c \
		$(SRC_DIR)/ray_caster/cast_rays.c $(SRC_DIR)/ray_caster/minimap.c $(SRC_DIR)/ray_caster/minimap_rays.c \
		$(SRC_DIR)/ray_caster/textures.c  $(SRC_DIR)/parsing/flood_fill.c $(SRC_DIR)/ray_caster/cast_rays2.c \
		$(SRC_DIR)/moves/keycallback.c $(SRC_DIR)/init/init_helper.c

OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

BNS_SRC	= 	$(BNS_SRC_DIR)/main.c $(BNS_SRC_DIR)/parsing/file_parsing_bonus.c $(BNS_SRC_DIR)/parsing/utility_bonus.c \
			$(BNS_SRC_DIR)/garbage_collector/garbage_collector.c $(BNS_SRC_DIR)/parsing/map_parsing_bonus.c \
			$(BNS_SRC_DIR)/parsing/map_parsing_util_bonus.c $(BNS_SRC_DIR)/init/init_bonus.c $(BNS_SRC_DIR)/moves/move_player_bonus.c \
			$(BNS_SRC_DIR)/ray_caster/cast_rays_bonus.c $(BNS_SRC_DIR)/ray_caster/minimap_bonus.c $(BNS_SRC_DIR)/ray_caster/textures_bonus.c \
			$(BNS_SRC_DIR)/parsing/flood_fill_bonus.c $(BNS_SRC_DIR)/ray_caster/minimap_rays_bonus.c $(BNS_SRC_DIR)/ray_caster/helper_bonus.c \
			$(BNS_SRC_DIR)/ray_caster/cast_rays2_bonus.c $(BNS_SRC_DIR)/moves/keycallback_bonus.c $(BNS_SRC_DIR)/init/init_helper_bonus.c

BNS_OBJ	= $(patsubst $(BNS_SRC_DIR)/%.c, $(BNS_OBJ_DIR)/%.o, $(BNS_SRC))

all: libmlx libft $(OBJ_DIR) $(NAME)
bonus: libmlx libft $(BNS_OBJ_DIR) $(BONUS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft: 
	$(MAKE) -C $(LIBFT)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(BNS_OBJ_DIR):
	@mkdir -p $(BNS_OBJ_DIR)

$(BNS_OBJ_DIR)/%.o: $(BNS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(BONUS_NAME): $(BNS_OBJ)
	@$(CC) $(BNS_OBJ) $(LIBS) $(HEADERS) -o $(BONUS_NAME)

clean:
	rm -rf $(OBJ_DIR) $(BNS_OBJ_DIR)
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(LIBMLX)/build clean

fclean: clean
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, libft bonus