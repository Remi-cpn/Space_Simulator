# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 17:34:44 by rcompain          #+#    #+#              #
#    Updated: 2026/05/05 16:29:03 by rcompain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = librt.a

CC = cc

FLAGS = -Werror -Wextra -Wall -g

# ——— Sources ———————————————————————————————————————————————————————————————— #
SRC_VEC =	vec/vec_add.c \
			vec/vec_dot.c \
			vec/vec_init.c \
			vec/vec_mult_scalar.c \
			vec/vec_norm.c \
			vec/vec_normalize.c \
			vec/vec_square.c \
			vec/vec_sub.c \
			vec/vec_vectoriel.c \
			vec/vec_proj.c

SRC_PAR =	parsing/double_valid.c \
			parsing/float_valid.c \
			parsing/int_valid.c \
			parsing/long_valid.c \
			parsing/print_error.c \
			parsing/check_extention.c \
			parsing/check_idx_string.c

SOURCES = $(SRC_VEC) $(SRC_PAR)

OBJECTS = ${SOURCES:.c=.o}

# ——— Rules —————————————————————————————————————————————————————————————————— #
%.o: %.c
	@${CC} ${FLAGS} -c $< -o $@
	@printf "\r\033[2K$(CYAN)Compiled files: %s$(RESET)" "$<"
	@sleep 0.02

${NAME}: ${OBJECTS} 
	@ar rcs ${NAME} ${OBJECTS} 

all: ${NAME}

clean:
	@rm -rf ${OBJECTS}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

# ——— Decos —————————————————————————————————————————————————————————————————— #
CYAN		= \033[36m
RESET		= \033[0m


.PHONY: all clean fclean re
