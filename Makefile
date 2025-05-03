#***************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/15 12:58:06 by mmarinov          #+#    #+#              #
#    Updated: 2025/05/03 19:13:26 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Libraries and options
READLINE = -lreadline
SANITIZE = -g -fsanitize=address
RM = rm -rf

# Files and folders
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_FOLDER = inc
SRC_PATH = src
OBJ_DIR = obj
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CC = clang
else
	CC = cc
endif

CFLAGS = -Wall -Wextra -Werror -MMD -I$(INC_FOLDER) -I$(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR)

# Specify the main header file
INCLUDES = minishell.h shell_types.h sys_includes.h

# Specify the main header file
SRC_FOLDER =  main.c signals/signals.c
SRC_FOLDER += parser/helper.c parser/expand_var.c parser/parse_tokens.c \
			  parser/parser_utils.c parser/expand_helper.c
SRC_FOLDER += lexer/lex_tokens.c
SRC_FOLDER += tokenizer/tokenizer.c tokenizer/tokenizer_utils.c
SRC_FOLDER += builtins/ft_env.c builtins/ft_exit.c builtins/ft_cd.c     \
			  builtins/ft_echo.c builtins/ft_getenv.c builtins/ft_pwd.c \
			  builtins/ft_export.c builtins/ft_unset.c                   \
			  builtins/ft_export_util.c builtins/core.c
SRC_FOLDER += exec/exec.c exec/find_cmd_path.c exec/exec_utils.c
SRC_FOLDER += utils/inits.c utils/main_utils.c utils/memory_management.c
SRC_FOLDER += utils/string.c
SRC_FOLDER += pipes/heredoc.c pipes/pipes.c pipes/redir.c pipes/utils_pipe.c

# Add header paths, source paths, objects, dependency files
INC_H = $(addprefix $(INC_FOLDER)/,$(INCLUDES))
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_FOLDER))
OBJS = $(patsubst $(SRC_PATH)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Dependency file, default command and dependency for the libft
DEPS = $(OBJS:.o=.d)

.PHONY: all
all: $(NAME)

# Dependency for libft now includes this Makefile
$(LIBFT): $(LIBFT_DIR)/Makefile Makefile
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

# To create the final executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS) $(READLINE)
	@echo -- "\033[1;32mminishell created \033[0m"

# To compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c $(INC_H) Makefile
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

# Include dependency files
-include $(DEPS)

.PHONY: clean
clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

