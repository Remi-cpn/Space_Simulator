
# **************************************************************************** #
#   Space_Simulator — Makefile                                                 #
#   Compile le simulateur et vérifie les dépendances (check-deps).             #
#   Usage : make [all | clean | fclean | re | check-deps]                      #
# **************************************************************************** #

NAME 		= Space_Simulator
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lSDL2 -lm -lpthread -lGL -ldl
INCLUDES	= -Iexternal/glad/include -Iexternal/stb
RM			= rm -f
SETUP 		:= ./scripts/setup.sh


# ——— Dossier cible —————————————————————————————————————————————————————————— #
SRC_DIR		= srcs
OBJ_DIR		= obj
LIBFT_DIR	= library/libft
LIBRT_DIR	= library/librt
LIBFT_A		= $(LIBFT_DIR)/libft.a
LIBRT_A		= $(LIBRT_DIR)/librt.a
LIB			= $(LIBFT_A) $(LIBRT_A)


# ——— Sous-dossiers sources —————————————————————————————————————————————————— #
SUB_DIRS 	:= exit init debug shaders events parsing moves


# ——— Sources ———————————————————————————————————————————————————————————————— #
SRC_INIT	= init_program.c \
			  init_image.c \
			  init_texture.c \
			  init_simulation.c \
			  init_hud.c

SRC_EXIT	= exit_program.c

SRC_DEBUG	= gl_debug.c \
			  hud.c \
			  hud_db.c

SRC_SHADER	= shader.c

SRC_EVENTS	= poll_events.c

SRC_PARSING	= parsing.c \
			  parsing_file.c \
			  parsing_texture.c \
			  utils.c \
			  format/format_unique.c \
			  format/format_ss.c

SRC_MOVES	= camera.c

VPATH 		:= $(SRC_DIR) \
         		$(addprefix $(SRC_DIR)/, $(SUB_DIRS))

SRCS		= srcs/main.c external/glad/src/gl.c $(SRC_INIT) $(SRC_EXIT) $(SRC_DEBUG) $(SRC_SHADER) $(SRC_EVENTS) $(SRC_PARSING) $(SRC_MOVES)

OBJ			= ${SRCS:%.c=$(OBJ_DIR)/%.o}


# ——— Colors ———————————————————————————————————————————————————————————————— #
R           = \033[0m
BOLD        = \033[22m\033[1m
DIM         = \033[2m
GREEN       = \033[32m
CYAN        = \033[36m
ORANGE      = \033[38;5;183m
RED         = \033[38;5;210m


# ——— Banner ———————————————————————————————————————————————————————————————— #


# ——— Rules ————————————————————————————————————————————————————————————————— #
all: $(LIB) $(NAME)

$(NAME): check-deps $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LIB) $(LFLAGS)
	@printf "\r\033[2K$(CYAN)📝 Sources     $(BOLD)$(GREEN)[OK]$(R)\n"
	@printf "$(BOLD)$(GREEN)\n    ✅  Space_Simulator compiled successfully\n\n$(R)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiling   %s$(R)" "$<"

$(LIBFT_A):
	@make -s -C $(LIBFT_DIR)
	@printf "\r\033[2K$(CYAN)📚 Libft       $(BOLD)$(GREEN)[OK]$(R)\n"

$(LIBRT_A):
	@make -s -C $(LIBRT_DIR)
	@printf "\r\033[2K$(CYAN)🪐 Librt       $(BOLD)$(GREEN)[OK]$(R)\n"

check-deps:
	@command -v sdl2-config >/dev/null 2>&1 || { \
		printf "Missing SDL2 — launch $(SETUP) ? [y/N] "; \
		read answer; \
		[ "$$answer" = "y" ] && sh $(SETUP) || \
			{ echo "Installation cancelled."; exit 1; }; \
	}

clean:
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(LIBRT_DIR)
	@$(RM) -r $(OBJ_DIR)
	@printf "$(CYAN)🗑  Object files removed$(R)\n"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@make fclean -s -C $(LIBRT_DIR)
	@$(RM) $(NAME)
	@printf "$(CYAN)🗑  Executable removed$(R)\n"

re: fclean all

.PHONY: all clean fclean re check-deps