### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3

### PROJECT NAME ###
NAME := cub3d
BONUS_NAME := cub3d_bonus

### SOURCE DIR ###

SRC_DIR := src
EXEC_DIR := $(SRC_DIR)/exec
PARSING_DIR := $(SRC_DIR)/parsing
INCLUDES_DIR := -I ./include

##MLX
MLX_DIR := ./include/minilibx
MLXFLAGS = -I/usr/include -Imlx_linux -O3 -lXext -lX11 -lm
MLX := $(MLX_DIR)/libmlx.a

##LIBFT
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

# CURSOR MOVEMENTS
MOV_U			=	\033[1A
MOV_D			=	\033[1B
MOV_F			=	\033[1C
MOV_B			=	\033[1D

ERASE_ALL		=	\033[0J

# COLORS 
YELLOW			=	\033[0;33m
GREEN			=	\033[0;32m
BLUE			=	\033[0;34m
RED				=	\033[0;31m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
BLACK			=	\033[0;30
WHITE			=	\033[0;37m

# *************************************************************************** #
#                             MANDATORY SOURCE FILE                           #
# *************************************************************************** #
SRC_FILE := main.c \
			utils/print.c \
			utils/keys_management.c

EXEC_FILE := dda.c \
			draw.c \
			draw_utils.c \
			error.c \
			utils.c \
			init.c \
			game.c \
			hooks.c

PARSING_FILE := parsing.c	\
			map.c	\
			utils_identifiers.c	\
			utils_parsing.c \
			utils_map.c 

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE))
EXEC = $(addprefix $(EXEC_DIR)/, $(EXEC_FILE))
PARSING = $(addprefix $(PARSING_DIR)/, $(PARSING_FILE))

## OBJECT FILE ###
OBJ_DIR := .obj
OBJ_SRC := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_EXEC := $(patsubst $(EXEC_DIR)/%.c, $(OBJ_DIR)/%.o, $(EXEC))
OBJ_PARSING := $(patsubst $(PARSING_DIR)/%.c, $(OBJ_DIR)/%.o, $(PARSING))
OBJ := $(OBJ_SRC) $(OBJ_EXEC) $(OBJ_PARSING)

OBJ_BONUS_DIR := .obj_bonus
OBJ_BONUS_SRC := $(patsubst $(SRC_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(SRC))
OBJ_BONUS_EXEC := $(patsubst $(EXEC_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(EXEC))
OBJ_BONUS_PARSING := $(patsubst $(PARSING_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(PARSING))
OBJ_BONUS := $(OBJ_BONUS_SRC) $(OBJ_BONUS_EXEC) $(OBJ_BONUS_PARSING)

# *************************************************************************** #
#                                SRC COMPILE OBJ                              #
# *************************************************************************** #

all : $(NAME)
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR)  -c $< -o $@ 

$(OBJ_DIR)/%.o : $(EXEC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR)  -c $< -o $@

$(OBJ_DIR)/%.o : $(PARSING_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR)  -c $< -o $@

$(OBJ_BONUS_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR) -DBONUS=1 -c $< -o $@

$(OBJ_BONUS_DIR)/%.o : $(EXEC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR) -DBONUS=1 -c $< -o $@

$(OBJ_BONUS_DIR)/%.o : $(PARSING_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR) -DBONUS=1 -c $< -o $@

$(LIBFT) :
	@make -C $(LIBFT_DIR) --silent

$(MLX) :
	@if [ ! -d "include/minilibx" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) > /dev/null 2>&1; \
	fi
	@make -C $(MLX_DIR) --silent > /dev/null 2>&1;

$(NAME) : $(MLX) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@make --silent banner

$(BONUS_NAME) : $(MLX) $(OBJ_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) -DBONUS=1 $(OBJ_BONUS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(BONUS_NAME)
	@make --silent banner

fclean : clean
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C libft fclean --silent

clean :
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) $(MLX_DIR)
	@make -C libft clean --silent

re : clean fclean all

bonus : $(BONUS_NAME)

banner :
	@echo "$(RED)	 _____ _   _______  ___________ "
	@echo "	/  __ \ | | | ___ \|____ |  _  \\"
	@echo "	| /  \/ | | | |_/ /    / / | | |"
	@echo "	| |   | | | | ___ \    \ \ | | |"
	@echo "	| \__/\ |_| | |_/ /.___/ / |/ / "
	@echo "	 \____/\___/\____/ \____/|___/  "
	@echo ""

.PHONY : all clean fclean banner re bonus