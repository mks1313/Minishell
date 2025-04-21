# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/15 12:58:06 by mmarinov          #+#    #+#              #
#    Updated: 2025/04/21 15:53:01 by mmarinov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Librerías y opciones
READLINE = -lreadline
SANITIZE = -g #-fsanitize=address
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

ifeq ($(UNAME), Darwin)
	CC = clang
else
	CC = cc
endif

# -----------------------------------------------------------------------------#
#           Correctly specify the header paths                                 #
#------------------------------------------------------------------------------#
CFLAGS = -Wall -Wextra -Werror  -MMD -I$(INC_FOLDER) -I$(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR)

#------------------------------------------------------------------------------#
#           Specify the main header file                                       #
#------------------------------------------------------------------------------#

INCLUDES = minishell.h shell_types.h sys_includes.h

#------------------------------------------------------------------------------#
#           Specify the main header file                                       #
#------------------------------------------------------------------------------#

SRC_FOLDER =  main.c signals/signals.c
SRC_FOLDER += parser/helper.c parser/expand_var.c parser/parse_tokens.c \
			  parser/parser_utils.c parser/expand_helper.c
SRC_FOLDER += lexer/lex_tokens.c
SRC_FOLDER += tokenizer/tokenizer.c tokenizer/tokenizer_utils.c
SRC_FOLDER += built_ins/ft_env.c built_ins/ft_exit.c built_ins/ft_cd.c     \
			  built_ins/ft_echo.c built_ins/ft_getenv.c built_ins/ft_pwd.c \
			  built_ins/ft_export.c built_ins/ft_unset.c                   \
			  built_ins/ft_export_util.c built_ins/builtins_utils.c
SRC_FOLDER += exec/exec.c exec/find_cmd_path.c exec/exec_utils.c
SRC_FOLDER += utils/inits.c utils/main_utils.c utils/free_data.c           \
			  utils/free_data_utils.c
SRC_FOLDER += pipes/execute_child.c pipes/heredoc.c pipes/pipes.c          \
			  pipes/redir.c pipes/utils_pipe.c

#------------------------------------------------------------------------------#
#           Add header paths, source paths, objects, dependency files          #
#------------------------------------------------------------------------------#

INC_H = $(addprefix $(INC_FOLDER)/,$(INCLUDES))
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_FOLDER))
OBJS = $(patsubst $(SRC_PATH)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

#------------------------------------------------------------------------------#
#            Dependency files                                                  #
#------------------------------------------------------------------------------#

DEPS = $(OBJS:.o=.d)

#------------------------------------------------------------------------------#
#            Default commands                                                  #
#------------------------------------------------------------------------------#

all: $(NAME)

#------------------------------------------------------------------------------#
#            Dependency for the libft library                                  #
#------------------------------------------------------------------------------#

$(LIBFT):
	make -C $(LIBFT_DIR)

#------------------------------------------------------------------------------#
#             Rule for creating the final binary                               #
#------------------------------------------------------------------------------#

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS) $(READLINE)
	@echo -- "\033[1;32mMiniShell created \033[0m"

#------------------------------------------------------------------------------#
#             Rule to compile source files to object files                     #
#------------------------------------------------------------------------------#

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c $(INC_H) Makefile
	mkdir -p $(dir $@)  # Asegura que el directorio de objetos se cree
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

#------------------------------------------------------------------------------#
#             Include dependency files                                         #
#------------------------------------------------------------------------------#

-include $(DEPS)

#------------------------------------------------------------------------------#
#              Clean generated objects                                         #
#------------------------------------------------------------------------------#

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

#------------------------------------------------------------------------------#
#              Clean everything (objects and executables)                      #
#------------------------------------------------------------------------------#

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

#------------------------------------------------------------------------------#
#               Reload everything                                              #
#------------------------------------------------------------------------------#

re: fclean all

.PHONY: all clean fclean re
