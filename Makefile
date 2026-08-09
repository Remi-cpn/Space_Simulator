
# **************************************************************************** #
#	Laniakea — setup.sh                                                        #
#	Installe les dépendances système nécessaires à la compilation.             #
#	Usage : ./setup.sh  													   #
# **************************************************************************** #

NAME 		= Laniakea
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f


# ——— Dossier cible —————————————————————————————————————————————————————————— #
SRC_DIR		= $src
OBJ_DIR		= obj
INC_DIR		= $include


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

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) -o $(NAME) -lSDL2 -lm -lpthread
	@printf "\r\033[2K$(CYAN)📝 Sources     $(BOLD)$(GREEN)[OK]$(R)\n"
	@printf "$(BOLD)$(GREEN)\n    ✅  minirt compiled successfully\n\n$(R)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiling   %s$(R)" "$<"

clean:
	@$(RM) -r obj
	@printf "$(CYAN)🗑  Object files removed$(R)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(CYAN)🗑  Executable removed$(R)\n"

re: fclean all

.PHONY: all clean fclean re 