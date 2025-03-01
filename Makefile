# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 16:51:41 by mmarinov          #+#    #+#              #
#    Updated: 2025/03/01 14:34:35 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft/includes
SANITIZE= -g -fsanitize=address
READLINE = -lreadline

# TODO: FIX RELINK MAKEFILES
NAME = minishell
INCLUDE = minishell.h

LIBFT = libft/libft.a

SRC = main.c signals.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJ) -o $@ $(READLINE) -Llibft -lft

%.o:%.c $(INCLUDE) Makefile
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

clean:
	@make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	@make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
