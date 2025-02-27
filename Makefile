# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 16:51:41 by mmarinov          #+#    #+#              #
#    Updated: 2025/02/26 16:51:59 by mmarinov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE= -g -fsanitize=address
READLINE = -lreadline

NAME = minishell
INCLUDE = minishell.h

SRC = main.c signals.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJ) -o $(NAME) $(READLINE)

%.o:%.c $(INCLUDE) Makefile
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
