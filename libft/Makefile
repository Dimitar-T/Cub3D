CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
      ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o \
      ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o \
      ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o \
      ft_strnstr.o ft_atoi.o ft_substr.o ft_strtrim.o ft_strjoin.o \
	  ft_calloc.o ft_split.o ft_itoa.o ft_strdup.o ft_strcmp.o\
	  ft_strmapi.o ft_striteri.o ft_putstr_fd.o ft_putendl_fd.o \
	  ft_putchar_fd.o ft_putnbr_fd.o ft_printf/ft_print_hex.o\
	  ft_printf/ft_print_num.o ft_printf/ft_printf.o \
	  get_next_line/get_next_line.o get_next_line/get_next_line_utils.o \
	  ft_lstnew_bonus.o ft_lstadd_front_bonus.o ft_lstsize_bonus.o ft_lstlast_bonus.o \
	  ft_lstadd_back_bonus.o ft_lstdelone_bonus.o ft_lstclear_bonus.o \
	  ft_lstiter_bonus.o ft_lstmap_bonus.o

OBJ = $(SRC:.o=.o)
NAME = libft.a
HEADER = libft.h
PRINTF_HEADER = ft_printf/ft_printf.h
GNL_HEADER = get_next_line/get_next_line.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^  # Archive command to create the static library

%.o: %.c $(HEADER) $(PRINTF_HEADER) $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)  # Remove object files

fclean: clean
	rm -f $(NAME)  # Remove the static library

re: fclean all

.PHONY: all clean fclean re