# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchi <pchi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 20:15:31 by pchi              #+#    #+#              #
#    Updated: 2024/10/09 20:34:00 by pchi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC		= cc

CFLAGS		= -Wall -Wextra -Werror

RM = rm -rf

SRC = 	pipex.c\
		main.c\
		libft/libft.a\

$(NAME) :
	make all -C libft
	gcc $(CFLAGS) $(SRC) -o $(NAME)

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all
