# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 17:34:44 by rcompain          #+#    #+#              #
#    Updated: 2026/04/13 11:44:34 by rcompain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME = libft.a

CC = cc

FLAGS = -Werror -Wextra -Wall -g

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC = 		ft_atoi.c \
			ft_atol.c \
			ft_atof.c \
			ft_atod.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_iswhitespace.c \
			ft_isoneof.c \
			ft_skip_whitespace.c \
			ft_itoa.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_count_word.c \
			ft_occurence.c \
			ft_strndup.c \
			ft_get_next_line.c \

SRC_PUT =	ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \

SRC_MEM = 	ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_freenull.c \
			ft_realloc.c \
			ft_freedbptr.c \
			ft_free_array.c \

SRC_LST =	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

SRC_PTF =	ft_printf.c \
			ft_putstr.c \
			ft_putnbrbase.c \
			ft_putchar.c \
			ft_putadrbase.c \
			ft_putnbr.c \

SOURCES = $(SRC) $(SRC_PUT) $(SRC_MEM) $(SRC_LST) $(SRC_PTF)

OBJECTS = ${SOURCES:.c=.o}

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

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

# **************************************************************************** #
#                                   DECO & COLORS                              #
# **************************************************************************** #

CYAN		= \033[36m
RESET		= \033[0m


.PHONY: all clean fclean re
