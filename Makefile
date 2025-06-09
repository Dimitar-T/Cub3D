NAME	= cub3D
CFLAGS	= -Wextra -Wall -Wunreachable-code -O3 -g 
LIBMLX	= ./MLX42
LIBFT = ./libft

HEADERS = -I ./include -I $(LIBMLX)/include -I $(LIBMLX) $(INCLUDES)
LDFLAGS = -L/opt/homebrew/lib
INCLUDES = -I/opt/homebrew/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm $(LIBFT)/libft.a $(LDFLAGS)

SRC_DIR = src
OBJ_DIR = obj

SRC	= 	$(SRC_DIR)/main.c $(SRC_DIR)/parsing/file_parsing.c $(SRC_DIR)/parsing/utility.c \
		$(SRC_DIR)/garbage_collector/garbage_collector.c $(SRC_DIR)/parsing/map_parsing.c \
		$(SRC_DIR)/parsing/map_parsing_util.c

OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: libmlx libft $(OBJ_DIR) $(NAME)

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

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, libft