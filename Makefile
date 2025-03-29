# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/15 12:58:06 by mmarinov          #+#    #+#              #
#    Updated: 2025/03/29 12:30:35 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Librerías y opciones
READLINE = -lreadline
SANITIZE = -g -fsanitize=address
# importante el -r
RM = rm -rf

# Directorios y archivos
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_FOLDER = inc
SRC_PATH = src
OBJ_DIR = obj
#   CC = cc
UNAME := $(shell uname)

ifeq ($(UNMAE), Darwin)
	CC = clang
else
	CC = cc
endif

# Correctamente especificamos las rutas de cabecera
CFLAGS = -Wall -Wextra -Werror -I$(INC_FOLDER) -I$(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR)

# Especificamos el archivo de cabecera principal
INCLUDES = minishell.h shell_types.h sys_includes.h

# Carpeta de fuentes y archivos
SRC_FOLDER =  main.c inits.c utils.c free_data.c signals/signals.c
SRC_FOLDER += parser/quotes.c
SRC_FOLDER += lexer/lexer.c tokenizer/tokenizer.c
SRC_FOLDER += built_ins/ft_env.c built_ins/ft_exit.c built_ins/ft_cd.c  \
			  built_ins/ft_echo.c built_ins/ft_getenv.c
SRC_FOLDER += built_ins/builtins_utils.c
SRC_FOLDER += exec/exec.c exec/exec_utils.c
# Agregamos las rutas de headers
INC_H = $(addprefix $(INC_FOLDER)/,$(INCLUDES))

# Agregamos la ruta a las fuentes
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_FOLDER))

# Definimos los objetos a generar a partir de las fuentes
OBJS = $(patsubst $(SRC_PATH)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Comando por defecto
all: $(NAME)

# Dependencia de la biblioteca libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Regla para la creación del binario final
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS) $(READLINE)
	@echo -- "\033[1;32mMiniShell created \033[0m"

# Regla para compilar los archivos fuente a objetos
$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c $(INC_H) Makefile
	mkdir -p $(dir $@)  # Asegura que el directorio de objetos se cree
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

# Limpiar objetos generados
clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

# Limpiar todo (objetos y ejecutable)
fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

# Recargar todo
re: fclean all

.PHONY: all clean fclean re
