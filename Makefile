
# **************************************************************************** #
#   Space_Simulator — Makefile                                                 #
#   Compile le simulateur et vérifie les dépendances (check-deps).             #
#   Usage : make [all | clean | fclean | re | check-deps]                      #
# **************************************************************************** #

NAME 		= Space_Simulator
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lSDL2 -lm -lpthread -lGL -ldl
RM			= rm -f
SETUP 		:= ./scripts/setup.sh


# ——— Dossier cible —————————————————————————————————————————————————————————— #
SRC_DIR		= srcs
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= library/libft

LIBFT_A		= $(LIBFT_DIR)/libft.a


# ——— Sous-dossiers sources —————————————————————————————————————————————————— #
SUB_DIRS 	:= exit init


# ——— Sources ———————————————————————————————————————————————————————————————— #
SRC_INIT	= init_program.c

SRC_EXIT	= exit_program.c


VPATH 		:= $(SRC_DIR) \
         		$(addprefix $(SRC_DIR)/, $(SUB_DIRS))

SRCS		= main.c $(SRC_INIT) $(SRC_EXIT)

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
all: $(LIBFT_A) $(NAME)

$(NAME): check-deps $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) -o $(NAME) $(LIBFT_A) $(LFLAGS)
	@printf "\r\033[2K$(CYAN)📝 Sources     $(BOLD)$(GREEN)[OK]$(R)\n"
	@printf "$(BOLD)$(GREEN)\n    ✅  Space_Simulator compiled successfully\n\n$(R)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiling   %s$(R)" "$<"

$(LIBFT_A):
	@make -s -C $(LIBFT_DIR)
	@printf "\r\033[2K$(CYAN)📚 Libft       $(BOLD)$(GREEN)[OK]$(R)\n"

check-deps:
	@command -v sdl2-config >/dev/null 2>&1 || { \
		printf "Missing SDL2 — launch $(SETUP) ? [y/N] "; \
		read answer; \
		[ "$$answer" = "y" ] && sh $(SETUP) || \
			{ echo "Installation cancelled."; exit 1; }; \
	}

clean:
	@make clean -s -C $(LIBFT_DIR)
	@$(RM) -r $(OBJ_DIR)
	@printf "$(CYAN)🗑  Object files removed$(R)\n"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@printf "$(CYAN)🗑  Executable removed$(R)\n"

re: fclean all

.PHONY: all clean fclean re check-deps