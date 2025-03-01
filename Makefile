# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 16:51:41 by mmarinov          #+#    #+#              #
#    Updated: 2025/03/01 17:59:32 by mmarinov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_FOLDER)
SANITIZE= -g -fsanitize=address
READLINE = -lreadline

LIBFT = libft/libft.a
INC_FOLDER = inc
SRC_PATH = src
OBJ_DIR = obj

# TODO: FIX RELINK MAKEFILES

INCLUDE = $(INC_FOLDER)/minishell.h

SRC_FOLDER =  main.c
SRC_FOLDER += signals/signals.c
SRC_FOLDER += parser/quotes.c parser/lexer.c
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_FOLDER))
OBJS = $(patsubst $(SRC_PATH)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJ) -o $@ $(READLINE) -Llibft -lft

$(OBJ_DIR)/%.o:$(SRC_PATH)/%.c $(INCLUDE) Makefile
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
