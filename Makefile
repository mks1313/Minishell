# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 16:28:35 by mmarinov          #+#    #+#              #
#    Updated: 2025/02/23 13:22:30 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE= -g #-fsanitize=address

NAME = minishell
INCLUDE = minishell.h

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJ) -o $(NAME) -lreadline

%.o:%.c $(INCLUDE) Makefile
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
