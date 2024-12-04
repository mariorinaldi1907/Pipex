# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrinaldi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 14:47:36 by nrinaldi          #+#    #+#              #
#    Updated: 2024/01/22 14:47:45 by nrinaldi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
NAME		=       pipex
#
SOURCE		=       pipex.c env.c utils.c utils2.c
#
CFLAGS		= -Wall -Werror -Wextra -I.
HEADER		= pipex.h

OBJ = $(SOURCE:%.c=%.o)
CC = gcc
#
.PHONY : all clean fclean re bonus
#
all: $(NAME)
$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
#
%.o	: %.c $(HEADER)
	$(CC) $(CFLAGS)	-c $< -o $@
#
clean	:
	@rm -f $(OBJ)
#
fclean	: clean
	@rm -f $(NAME)
re	:	fclean all

