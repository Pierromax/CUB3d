### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3

### PROJECT NAME ###
NAME := CUB3D

### SOURCE DIR ###

SRC_DIR := src
PARSING_DIR := $(SRC_DIR)/parsing
INCLUDES_DIR := -I ./include


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
			error.c

PARSING_FILE := parsing.c	\
			map.c	\
			utils_identifiers.c	\
			utils_parsing.c \
			utils_map.c 

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE))
PARSING = $(addprefix $(PARSING_DIR)/, $(PARSING_FILE))

## OBJECT FILE ###
OBJ_DIR := .obj
OBJ_SRC := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_PARSING := $(patsubst $(PARSING_DIR)/%.c, $(OBJ_DIR)/%.o, $(PARSING))
OBJ := $(OBJ_SRC) $(OBJ_PARSING)


# *************************************************************************** #
#                                SRC COMPILE OBJ                              #
# *************************************************************************** #

all : $(NAME) 

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)/%.o : $(PARSING_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(LIBFT) :
	@make -C $(LIBFT_DIR) --silent

$(NAME) : $(OBJ) $(LIBFT) banner
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

fclean : clean
	@rm -f $(NAME)
	@make -C libft fclean --silent

clean :
	@rm -rf $(OBJ_DIR)
	@make -C libft clean --silent

re : clean fclean all

banner:
	@echo "$(RED)	 _____ _   _______  ___________ "
	@echo "	/  __ \ | | | ___ \|____ |  _  \\"
	@echo "	| /  \/ | | | |_/ /    / / | | |"
	@echo "	| |   | | | | ___ \    \ \ | | |"
	@echo "	| \__/\ |_| | |_/ /.___/ / |/ / "
	@echo "	 \____/\___/\____/ \____/|___/  "
	@echo ""


.PHONY : all clean fclean banner re