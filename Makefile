NAME	= cub3D
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	= ./MLX42
LIBFT = ./libft

HEADERS	= -I ./include -I $(LIBMLX)/include -I $(LIBMLX)
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm $(LIBFT)/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRC	= 	$(SRC_DIR)/main.c $(SRC_DIR)/parsing/map_parsing.c $(SRC_DIR)/parsing/utility.c \
		$(SRC_DIR)/garbage_collector/garbage_collector.c
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

$(OBJ): $(SRC)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJ_DR)

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, libft