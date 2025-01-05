
# compilation variables

CC=			cc
NAME=		raycasting
CFLAGS=		-Wall -Wextra -Werror -g3
CFLAG_SAN=	-fsanitize=address
MLX_LINUX=	-Lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

# colors

LIGHT_BLUE = \033[38;2;53;200;240m
DARK_BLUE = \033[0;34m
ORANGE = \033[38;5;214m
PINK = \033[38;5;213m
BOLD = \033[1m
RESET_COLOR = \033[0m

###############################################################################

# src

SRC_DIR=	./src/
SRC=		main.c \
			player.c

# libft

LIBFT_DIR=	./libft/
LIBFT=		./libft/libft.a

# mlx

MLX_DIR=	./minilibx-linux
MLX=		./minilibx-linux/libmlx.a

###############################################################################

# objs
# mirar vpath
OBJ_DIR=	./obj/
OBJ=		$(SRC:%.c=$(OBJ_DIR)%.o)


###############################################################################

# rules

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Compiling libft...$(RESET_COLOR)"
	make -C $(LIBFT_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Compiling mlx_linux...$(RESET_COLOR)"
	make -C $(MLX_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Linking objs files with libraries...$(RESET_COLOR)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_LINUX) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD)$(DARK_BLUE)[$(NAME)]	Commpiling $<...$(RESET_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@


sanitize: fclean $(NAME)
	$(CC) $(CFLAGS) $(CFLAG_SAN) $(OBJ) $(LIBFT) $(MLX) $(MLX_LINUX) -o $(NAME)

clean:
	@echo "$(ORANGE)[$(NAME)]	Cleaning libft...$(RESET_COLOR)"
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	@echo "$(PINK)[$(NAME)]	Removing $(OBJ_DIR)...$(RESET_COLOR)"
	rm -rf $(OBJ)

fclean: clean
	@echo "$(BOLD)$(ORANGE)[$(NAME)]	fCleaning libft...$(RESET_COLOR)"
	make fclean -C $(LIBFT_DIR)
	@echo "$(ORANGE)[$(NAME)]	Cleaning mlx_linux..$(RESET_COLOR)"
	make clean -C $(MLX_DIR)
	@echo "$(BOLD)$(PINK)[$(NAME)]	Removing $(NAME)...$(RESET_COLOR)"
	rm -rf $(NAME)

norminette:
	@echo "$(BOLD)$(PINK)[$(NAME)]	Running norminette on all source files...$(RESET_COLOR)"
	norminette $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c

re: fclean all

.PHONY: sanitize clean fclean norminette re
