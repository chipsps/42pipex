# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchi <pchi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 20:15:31 by pchi              #+#    #+#              #
#    Updated: 2024/10/11 17:35:14 by pchi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC		= cc

CFLAGS		= -Wall -Wextra -Werror -ggdb

RM = rm -rf

SRC = 	pipex.c\
		main.c\

SRC_O =	$(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_O)
	make all -C libft
	cc $(CFLAGS) $(SRC) -o $(NAME) -L./libft -lft

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) *.o
	make clean -C libft

.PHONY: all re fclean clean