# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <mmarinov@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 13:27:43 by mmarinov          #+#    #+#              #
#    Updated: 2025/03/29 14:01:08 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g -Iincludes

INCL = includes/libft.h
OBJ_DIR = obj/

# Archivos fuente organizados por  carpetas
SRCS =  \
		src/num/ft_isalnum.c src/num/ft_atoi.c src/num/ft_isdigit.c \
		src/num/ft_itoa.c src/num/ft_utoa.c \
		src/char/ft_isalpha.c src/char/ft_isascii.c src/char/ft_isprint.c \
		src/char/ft_tolower.c src/char/ft_toupper.c src/char/ft_putchar.c \
		src/str/ft_strlen.c src/str/ft_strlcpy.c src/str/ft_strlcat.c \
		src/str/ft_strchr.c src/str/ft_strrchr.c src/str/ft_strncmp.c \
		src/str/ft_strnstr.c src/str/ft_strjoin.c src/str/ft_strtrim.c \
		src/str/ft_strmapi.c src/str/ft_split.c src/str/ft_striteri.c \
		src/str/ft_striteri.c src/str/ft_strncpy.c \
		src/mem/ft_memset.c src/mem/ft_memcpy.c src/mem/ft_strdup.c \
		src/mem/ft_memmove.c src/mem/ft_memchr.c src/mem/ft_memcmp.c \
    	src/mem/ft_calloc.c src/mem/ft_bzero.c src/mem/ft_substr.c \
		src/mem/ft_strndup.c  \
		src/lst/ft_lstnew.c src/lst/ft_lstadd_front.c src/lst/ft_lstsize.c \
		src/lst/ft_lstlast.c src/lst/ft_lstadd_back.c src/lst/ft_lstdelone.c \
		src/lst/ft_lstclear.c src/lst/ft_lstiter.c src/lst/ft_lstmap.c \
		src/files/ft_putchar_fd.c src/files/ft_putendl_fd.c\
		src/files/ft_putnbr_fd.c src/files/ft_putstr_fd.c \
		src/get_next_line/get_next_line.c \
		src/get_next_line/get_next_line_bonus.c src/printf/ft_printf.c \
		src/printf/utils_csp.c src/printf/utils_diuxx.c \
		src/str/ft_strtok.c src/utils/ft_getopt.c src/str/ft_strcmp.c \
		src/utils/ft_getpid.c src/str/ft_strstr.c

# Crear los objetos a partir de los archivos fuente
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)

# Regla principal
all: $(NAME)

# Regla para crear la librería estática
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo -- "\033[1;32mLibft created \033[0m"

# Regla para compilar cada archivo fuente en un archivo objeto
$(OBJ_DIR)%.o: %.c $(INCL) Makefile
	@mkdir -p $(@D)  # Crear el directorio correspondiente para cada objeto
	@$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos objeto generados
clean:
	@$(RM) $(OBJ_DIR)
	@echo -- "\033[1;31mCleaned objects \033[0m"

# Limpiar todos los archivos generados, incluidos los objetos y la librería
fclean: clean
	@$(RM) $(NAME)
	@echo -- "\033[1;31mCleaned libft \033[0m"

# Limpiar todo y luego recompilar
re: fclean all

.PHONY: all clean fclean re

