
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


# ——— Sous-dossiers sources —————————————————————————————————————————————————— #
SUB_DIRS 	:= 


# ——— Sources ———————————————————————————————————————————————————————————————— #



VPATH 		:= $(SRC_DIR) \
         		$(addprefix $(SRC_DIR)/, $(SUB_DIRS))

SRCS		= main.c

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
all: $(NAME)

$(NAME): check-deps $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) -o $(NAME) $(LFLAGS)
	@printf "\r\033[2K$(CYAN)📝 Sources     $(BOLD)$(GREEN)[OK]$(R)\n"
	@printf "$(BOLD)$(GREEN)\n    ✅  Space_Simulator compiled successfully\n\n$(R)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiling   %s$(R)" "$<"

check-deps:
	@command -v sdl2-config >/dev/null 2>&1 || { \
		printf "Missing SDL2 — launch $(SETUP) ? [y/N] "; \
		read answer; \
		[ "$$answer" = "y" ] && sh $(SETUP) || \
			{ echo "Installation cancelled."; exit 1; }; \
	}

clean:
	@$(RM) -r $(OBJ_DIR)
	@printf "$(CYAN)🗑  Object files removed$(R)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(CYAN)🗑  Executable removed$(R)\n"

re: fclean all

.PHONY: all clean fclean re check-deps