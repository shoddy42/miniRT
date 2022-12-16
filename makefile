# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: wkonings <wkonings@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 16:21:56 by wkonings      #+#    #+#                  #
#    Updated: 2022/12/16 22:00:45 by root          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ----------------------------------------- #
# --------------- VARIABLES --------------- #
# ----------------------------------------- #

NAME 	:= miniRT
FLAGS 	:= -pthread -mavx #-g -fsanitize=address  #-Wall -Wextra -Werror #//todo: RENABLE FLAGS WHEN HANDING IN FOR THE LOVE OF GOD
CFLAGS	:= -w -Wunreachable-code -Ofast
DEBUG 	:= #-g #-fsanitize=address
LIBS	:=	libft mlx
LIBMLX	:= mlx
LIBFT	:= libft
MAKEFILE:= makefile
CC		:= clang

# ---------------------------------------- #
# --------------- DIRECTORIES ------------ #d
# ---------------------------------------- #

#src and its subdirectories.
SRC_DIR		:= src
S_PARSER	:= parser

OBJ_DIR		:=	obj
# OBJ_BAD		:=	env executor builtins tokens parser
OBJ_SUB		:=	$(addprefix $(OBJ_DIR)/, $(OBJ_BAD))

BIN_DIR		:= bin
INCLUDE_DIR	:= include
LIB_DIR		:= libft

INCLUDES	:= libft/libft.a mlx/libmlx42.a -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/
HEADERS_DIR	:= include
INC			:= -I include

# ----------------------------------------- #
# --------------- FILES ------------------- #
# ----------------------------------------- #

#this cant be fully right?
HEADER_FILES:=	miniRT.h
HEADERS		:=	$(addprefix $(INCLUDE_DIR)/, $(HEADER_FILES))

MAIN_FILES	:= main keyhooks vectorlib

PARSER_FILES:= parser parse_objects parse_utils

FILES	:=	$(MAIN_FILES:%=%.c) \
			$(addprefix $(S_PARSER)/, $(PARSER_FILES:%=%.c)) \
			# $(addprefix $(S_TOKEN)/, $(TOKEN_FILES:%=%.c)) \
			# $(addprefix $(S_EXEC)/, $(EXEC_FILES:%=%.c)) \
			# $(addprefix $(S_ENV)/, $(ENV_FILES:%=%.c)) \
			# $(addprefix $(S_BUILTIN)/, $(BUILT_FILES:%=%.c))

SRCS	:=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJS	:=	$(addprefix $(OBJ_DIR)/, $(FILES:%.c=%.o))

# ----------------------------------------- #
# --------- COLOURS / FORMATTING ---------- #
# ----------------------------------------- #

#Formatting
RESET	:= \1\33[0m\2
END		:= \1\33[0m\2\3
BANNER	:= banner

#Colours
YELLOW	:= \1\33[38;5;220m\2
BLACK	:= \1\33[38;5;232m\2
ORANGE	:= \1\33[38;5;202m\2
RED		:= \1\33[38;5;196m\2
PINK	:= \1\33[38;5;198m\2
GREEN	:= \1\33[38;5;28m\2
BLUE	:= \1\33[38;5;33m\2
L_BLUE	:= \1\33[38;5;69m\2
D_BLUE	:= \1\33[38;5;21m\2
GREY	:= \1\33[38;5;242m\2
PURPLE	:= \1\33[38;5;92m\2
VIOLET	:= \1\33[38;5;183m\2

# ----------------------------------------- #
# --------------- RECIPES ----------------- #
# ----------------------------------------- #

#todo: dependancy on makefile
$(NAME): $(OBJS) $(HEADERS) $(MAKEFILE)
	@make all -C $(LIB_DIR)
	@make -C $(LIBMLX)
	@printf "$(BLUE)Compiling $(YELLOW)$(NAME).\n$(END)"
	@$(CC) -ldl -lglfw -lm $(FLAGS) $(DEBUG) $(SRCS) -o $(NAME) -I include -I mlx/include $(INCLUDES)
	@printf "$(YELLOW)miniRT compiled!\n$(END)"

all: $(BANNER) $(NAME)

$(LIBMLX):
	@git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

$(LIBFT):
	@git clone https://github.com/shoddy42/libft

# $(BIN_DIR):
# 	@printf "$(YELLOW)Creating $(RESET)/$@/ directory.\n$(END)"
# 	@mkdir -p $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(LIBFT) $(LIBMLX)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling $(PINK)$(notdir $@) $(RESET)from $(RED)$(notdir $<)$(END)\n"
	@$(CC) $(FLAGS) -I include $(INCLUDE_READLINE) -c $< -o $@

flags:
	$(CC) $(FLAGS) $(SOURCES) -lft $(INCLUDES) -lreadline $(READLINE_DIRS) $(INCLUDE_READLINE)
	./$(NAME)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean:	clean
	/bin/rm -f $(NAME)
	/bin/rm -rf $(BIN_DIR)

mrclean: fclean
	@make fclean -C $(LIBFT)

tooclean: fclean
	/bin/rm -rf $(LIBFT)
	/bin/rm -rf $(LIBMLX)

re: fclean all

#todo: make a git pull: which pulls from libft, mlx and minirt

tooreal: tooclean re

test: $(NAME)
	@./$(NAME)

pog:
	@printf "\n$(RED)"
	@printf "⣿⣿⣿⣿⡿⠟⠛⠛⠛⠛⠉⠉⠙⠛⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠟   \n"
	@printf "⣿⣿⣯⣥⣤⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣏⣀⣀⣀⡀  \n"
	@printf "⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠻⠿⠟⠉⠉⠉⢻⣿⣿⣿⡿⠟⠋⣡⣼⣿⣿⣿⡄ \n"
	@printf "⣿⣿⣿⣟⣭⣤⣶⣶⣿⣿⠃⠀⠀⢀⣀⣤⣶⣿⣿⣿⣿⡅⡀⢀⣩⣤⣤    \n"
	@printf "⣿⣿⣿⣿⣿⣿⣛⡛⠛⠛⠛⢋⣩⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣛⠛⠛⠓⠠   \n"
	@printf "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣤⣤⣤⣦  \n"
	@printf "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇ \n"
	@printf "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⢿⡿⢿⣿⣿⣿⠃ \n"
	@printf "⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣥⣄⣀⣀⠀⠀⠀⠀⠀⢰⣾⣿⣿⠏  \n"
	@printf "⠀⠀⠀⠀⠀⠀⠉⣩⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣜⡻⠋    \n"
	@printf "⣰⣾⣷⣶⣿⣾⣖⣻⣿⣿⡿⣿⣿⣿⣿⠿⠿⠟⠛⠛⠛⠋⠉⠉⢉⡽⠃    \n"
	@printf "⣿⣿⣿⣿⣿⣿⡉⠉⠉⠛⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⡤⠚⠉      \n"
	@printf "⠛⠛⣿⣿⣿⣿⣿⣿⣿⠉⠛⢶⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⡇        \n"
	@printf "⠠⣾⣿⣿⣿⣿⣿⠿⠟⠃⠀⠀⠀⠈⠲⣴⣦⣤⣤⣤⣶⡾⠁        \n"
	@printf "⠄⠈⠉⠻⢿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠛⠛⠉          \n"
	@printf "$(END)"

.PHONY: all clean fclean mrclean tooclean re tooreal test banner hell pog flags
